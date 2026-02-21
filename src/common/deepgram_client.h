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

#pragma once

#include "JuceHeader.h"
#include <string>
#include <functional>
#include <atomic>
#include <memory>

class DeepgramClient {
  public:
    using TranscriptCallback = std::function<void(const String& transcript, bool is_final)>;
    using ErrorCallback = std::function<void(const String& error)>;

    static DeepgramClient& instance();

    bool initialize();
    bool isInitialized() const { return initialized_; }

    bool connect(TranscriptCallback on_transcript, ErrorCallback on_error);
    void disconnect();
    bool isConnected() const { return connected_.load(); }

    void sendAudioData(const void* data, int num_bytes);

  private:
    DeepgramClient();
    ~DeepgramClient();
    DeepgramClient(const DeepgramClient&) = delete;
    DeepgramClient& operator=(const DeepgramClient&) = delete;

    bool loadApiKey();
    void processIncomingMessage(const std::string& message);

    std::string api_key_path_;
    std::string api_key_;
    bool initialized_ = false;
    std::atomic<bool> connected_{false};

    TranscriptCallback transcript_callback_;
    ErrorCallback error_callback_;
    String accumulated_transcript_;

    class Impl;
    std::unique_ptr<Impl> impl_;
};
