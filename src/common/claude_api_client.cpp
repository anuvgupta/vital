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

#include "claude_api_client.h"
#include "load_save.h"

namespace {
  const String kApiEndpoint = "https://api.anthropic.com/v1/messages";
  const String kModel = "claude-opus-4-20250514";
  const int kMaxTokens = 1024;
  const int kTimeoutMs = 30000;
}

ClaudeApiClient::ClaudeApiClient() { }

ClaudeApiClient& ClaudeApiClient::instance() {
  static ClaudeApiClient instance;
  return instance;
}

bool ClaudeApiClient::initialize() {
  api_key_path_ = LoadSave::getApiKeyPath();

  if (!loadApiKey()) {
    DBG("ClaudeApiClient: Failed to load API key from " + String(api_key_path_));
    initialized_ = false;
    return false;
  }

  internet_access_ = checkInternetAccess();
  if (!internet_access_)
    DBG("ClaudeApiClient: No internet access detected");

  initialized_ = true;
  DBG("ClaudeApiClient: Initialized successfully (internet: " + String(internet_access_ ? "yes" : "no") + ")");
  return true;
}

bool ClaudeApiClient::loadApiKey() {
  if (api_key_path_.empty()) {
    DBG("ClaudeApiClient: No API key path configured");
    return false;
  }

  File key_file(api_key_path_);
  if (!key_file.existsAsFile()) {
    DBG("ClaudeApiClient: API key file does not exist: " + String(api_key_path_));
    return false;
  }

  api_key_ = key_file.loadFileAsString().trim().toStdString();
  return !api_key_.empty();
}

bool ClaudeApiClient::checkInternetAccess() {
  URL url("https://claude.ai");
  std::unique_ptr<InputStream> stream(url.createInputStream(false, nullptr, nullptr, "", 5000));
  return stream != nullptr;
}

void ClaudeApiClient::sendMessage(const String& message, ResponseCallback callback) {
  if (!initialized_) {
    callback("API client not initialized. Please configure your API key.", false);
    return;
  }

  if (api_key_.empty()) {
    callback("API key not configured.", false);
    return;
  }

  // Run on background thread to avoid blocking UI
  Thread::launch([this, message, callback]() {
    sendMessageAsync(message, callback);
  });
}

void ClaudeApiClient::sendMessageAsync(const String& message, ResponseCallback callback) {
  // Build the JSON request body
  DynamicObject::Ptr requestBody = new DynamicObject();
  requestBody->setProperty("model", kModel);
  requestBody->setProperty("max_tokens", kMaxTokens);

  // Build messages array
  Array<var> messages;
  DynamicObject::Ptr userMessage = new DynamicObject();
  userMessage->setProperty("role", "user");
  userMessage->setProperty("content", message);
  messages.add(var(userMessage.get()));
  requestBody->setProperty("messages", messages);

  String jsonBody = JSON::toString(var(requestBody.get()));
  DBG("ClaudeApiClient: Sending request: " + jsonBody);

  // Build headers
  String headers = "x-api-key: " + String(api_key_) + "\r\n"
                   "anthropic-version: 2023-06-01\r\n"
                   "content-type: application/json";

  // Create URL and add POST data
  URL url(kApiEndpoint);
  url = url.withPOSTData(jsonBody);

  // Make the request using JUCE 6 API
  std::unique_ptr<InputStream> stream(url.createInputStream(
    true,           // isPost
    nullptr,        // progressCallback
    nullptr,        // progressCallbackContext
    headers,        // extraHeaders
    kTimeoutMs,     // timeoutMs
    nullptr,        // responseHeaders
    nullptr,        // statusCode
    0,              // numRedirectsToFollow
    "POST"          // httpRequestCmd
  ));

  if (!stream) {
    MessageManager::callAsync([callback]() {
      callback("Failed to connect to Claude API.", false);
    });
    return;
  }

  String response = stream->readEntireStreamAsString();
  DBG("ClaudeApiClient: Response: " + response);

  // Parse the response JSON
  var parsedResponse = JSON::parse(response);
  if (!parsedResponse.isObject()) {
    MessageManager::callAsync([callback]() {
      callback("Failed to parse API response.", false);
    });
    return;
  }

  // Check for error in response
  if (parsedResponse.hasProperty("error")) {
    var error = parsedResponse["error"];
    String errorMessage = "API Error";
    if (error.isObject() && error.hasProperty("message"))
      errorMessage = error["message"].toString();

    MessageManager::callAsync([callback, errorMessage]() {
      callback(errorMessage, false);
    });
    return;
  }

  // Extract the text content from the response
  // Response format: { "content": [{ "type": "text", "text": "..." }], ... }
  if (!parsedResponse.hasProperty("content")) {
    MessageManager::callAsync([callback]() {
      callback("Unexpected API response format.", false);
    });
    return;
  }

  var content = parsedResponse["content"];
  if (!content.isArray() || content.size() == 0) {
    MessageManager::callAsync([callback]() {
      callback("Empty response from API.", false);
    });
    return;
  }

  var firstContent = content[0];
  if (!firstContent.isObject() || !firstContent.hasProperty("text")) {
    MessageManager::callAsync([callback]() {
      callback("Unexpected content format in API response.", false);
    });
    return;
  }

  String responseText = firstContent["text"].toString();
  MessageManager::callAsync([callback, responseText]() {
    callback(responseText, true);
  });
}
