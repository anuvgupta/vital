/* Copyright 2013-2019 Matt Tytel
 *
 * vital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vital.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "deepgram_client.h"
#include "load_save.h"
#include "../../third_party/ixwebsocket/IXWebSocket.h"

// Forward-declare instead of including IXNetSystem.h to avoid
// pulling <winsock2.h>/<windows.h> into the unity build (which
// defines min/max macros that break std::min/std::max).
namespace ix { bool initNetSystem(); bool uninitNetSystem(); }

using json = nlohmann::json;

namespace {
  const std::string kDeepgramWsEndpoint =
      "wss://api.deepgram.com/v1/listen"
      "?encoding=linear16"
      "&sample_rate=16000"
      "&channels=1"
      "&model=nova-3"
      "&endpointing=1500"
      "&utterance_end_ms=2000"
      "&interim_results=true"
      "&smart_format=true";
}

class DeepgramClient::Impl {
  public:
    ix::WebSocket ws;
};

DeepgramClient::DeepgramClient() : impl_(std::make_unique<Impl>()) {
}

DeepgramClient::~DeepgramClient() {
  disconnect();
  ix::uninitNetSystem();
}

DeepgramClient& DeepgramClient::instance() {
  static DeepgramClient instance;
  return instance;
}

bool DeepgramClient::initialize() {
  ix::initNetSystem();
  initialized_ = false;
  if (!loadApiKey())
    return false;
  initialized_ = true;
  return true;
}

bool DeepgramClient::loadApiKey() {
  api_key_path_ = LoadSave::getDeepgramApiKeyPath();
  if (api_key_path_.empty()) {
    DBG("DeepgramClient: No API key path configured");
    return false;
  }

  File key_file(api_key_path_);
  if (!key_file.existsAsFile()) {
    DBG("DeepgramClient: API key file does not exist: " + api_key_path_);
    return false;
  }

  api_key_ = key_file.loadFileAsString().trim().toStdString();
  if (api_key_.empty()) {
    DBG("DeepgramClient: API key file is empty");
    return false;
  }

  DBG("DeepgramClient: API key loaded successfully");
  return true;
}

bool DeepgramClient::connect(TranscriptCallback on_transcript, ErrorCallback on_error) {
  if (!initialized_) {
    if (on_error)
      on_error("Deepgram client not initialized");
    return false;
  }

  if (connected_.load()) {
    disconnect();
  }

  transcript_callback_ = std::move(on_transcript);
  error_callback_ = std::move(on_error);
  accumulated_transcript_ = String();

  impl_->ws.setUrl(kDeepgramWsEndpoint);

  ix::WebSocketHttpHeaders headers;
  headers["Authorization"] = "Token " + api_key_;
  impl_->ws.setExtraHeaders(headers);

  impl_->ws.disableAutomaticReconnection();
  impl_->ws.disablePerMessageDeflate();

  impl_->ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
    switch (msg->type) {
      case ix::WebSocketMessageType::Open:
        DBG("DeepgramClient: WebSocket connected");
        connected_.store(true);
        break;

      case ix::WebSocketMessageType::Message:
        processIncomingMessage(msg->str);
        break;

      case ix::WebSocketMessageType::Error: {
        connected_.store(false);
        String error_msg = String("WebSocket error: ") + String(msg->errorInfo.reason);
        DBG("DeepgramClient: " + error_msg);
        if (error_callback_) {
          auto cb = error_callback_;
          MessageManager::callAsync([cb, error_msg]() {
            cb(error_msg);
          });
        }
        break;
      }

      case ix::WebSocketMessageType::Close:
        DBG("DeepgramClient: WebSocket closed");
        connected_.store(false);
        break;

      default:
        break;
    }
  });

  impl_->ws.start();

  // Wait briefly for connection to establish
  int wait_ms = 0;
  while (!connected_.load() && wait_ms < 5000) {
    Thread::sleep(50);
    wait_ms += 50;
  }

  if (!connected_.load()) {
    impl_->ws.stop();
    if (error_callback_) {
      auto cb = error_callback_;
      MessageManager::callAsync([cb]() {
        cb("Failed to connect to Deepgram (timeout)");
      });
    }
    return false;
  }

  return true;
}

void DeepgramClient::disconnect() {
  if (impl_) {
    impl_->ws.stop();
  }
  connected_.store(false);
  transcript_callback_ = nullptr;
  error_callback_ = nullptr;
  accumulated_transcript_ = String();
}

void DeepgramClient::sendAudioData(const void* data, int num_bytes) {
  if (!connected_.load() || !impl_)
    return;

  static int send_count = 0;
  if (send_count++ % 200 == 0)
    DBG("DeepgramClient: sendAudioData #" + String(send_count) + " bytes=" + String(num_bytes));

  impl_->ws.sendBinary(ix::IXWebSocketSendData(
      reinterpret_cast<const char*>(data), static_cast<size_t>(num_bytes)));
}

void DeepgramClient::processIncomingMessage(const std::string& message) {
  DBG("DeepgramClient: received message (" + String((int)message.size()) + " bytes): "
      + String(message.substr(0, 200)));

  try {
    json response = json::parse(message);

    std::string msg_type = response.value("type", "");
    DBG("DeepgramClient: message type=" + String(msg_type));

    if (msg_type == "UtteranceEnd") {
      // Utterance end detected - send accumulated transcript if any
      if (accumulated_transcript_.isNotEmpty() && transcript_callback_) {
        String final_text = accumulated_transcript_.trim();
        accumulated_transcript_ = String();
        auto cb = transcript_callback_;
        MessageManager::callAsync([cb, final_text]() {
          cb(final_text, true);
        });
      }
      return;
    }

    if (msg_type != "Results")
      return;

    auto& channel = response["channel"];
    auto& alternatives = channel["alternatives"];
    if (alternatives.empty())
      return;

    std::string transcript = alternatives[0].value("transcript", "");
    if (transcript.empty())
      return;

    bool is_final = response.value("is_final", false);
    bool speech_final = response.value("speech_final", false);

    DBG("DeepgramClient: transcript=\"" + String(transcript) + "\" is_final=" + String((int)is_final)
        + " speech_final=" + String((int)speech_final));

    if (speech_final) {
      // Endpointing detected - complete utterance
      accumulated_transcript_ += String(transcript) + " ";
      String final_text = accumulated_transcript_.trim();
      accumulated_transcript_ = String();
      if (transcript_callback_) {
        auto cb = transcript_callback_;
        MessageManager::callAsync([cb, final_text]() {
          cb(final_text, true);
        });
      }
    } else if (is_final) {
      // Final result for this audio segment, accumulate
      accumulated_transcript_ += String(transcript) + " ";
    } else {
      // Interim result - show as preview
      if (transcript_callback_) {
        String preview = accumulated_transcript_ + String(transcript);
        auto cb = transcript_callback_;
        MessageManager::callAsync([cb, preview]() {
          cb(preview, false);
        });
      }
    }
  } catch (const std::exception& e) {
    DBG("DeepgramClient: JSON parse error: " + std::string(e.what()));
  }
}
