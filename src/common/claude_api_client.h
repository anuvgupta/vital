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
#include <vector>

class ClaudeApiClient {
  public:
    using ResponseCallback = std::function<void(const String& response, bool success)>;
    using RouterCallback = std::function<void(const StringArray& actions, bool sound_design_required, bool success, const String& error)>;

    static ClaudeApiClient& instance();

    bool initialize();
    bool isInitialized() const { return initialized_; }
    bool hasInternetAccess() const { return internet_access_; }
    const std::string& getApiKey() const { return api_key_; }
    const std::string& getApiKeyPath() const { return api_key_path_; }

    void sendMessage(const String& message, ResponseCallback callback,
                     const String& preset_json = String());
    void sendMessages(const StringArray& messages, ResponseCallback callback,
                      const String& preset_json = String());

    // Router: analyzes a message and splits it into atomic actions via tool_use.
    // Does NOT modify conversation history.
    void routeMessage(const String& message, RouterCallback callback);

    // Sound design translation: converts non-technical descriptions into technical instructions.
    // Adds user message and translation response to conversation history.
    void sendSoundDesignTranslation(const String& message, ResponseCallback callback,
                                     const String& preset_json = String());

    // Add a message to conversation history without sending an API call.
    void addToHistory(const String& role, const String& content);

    void clearConversation();

    // Splits a response into plain text and JSON portions.
    // Handles code fences, raw JSON, and inline JSON without fences.
    static void splitResponseText(const String& response, String& textOut, String& jsonOut);
    void truncateHistoryTo(int size);

    int getHistorySize() const { return (int)conversation_history_.size(); }

  private:
    ClaudeApiClient();
    ~ClaudeApiClient() = default;
    ClaudeApiClient(const ClaudeApiClient&) = delete;
    ClaudeApiClient& operator=(const ClaudeApiClient&) = delete;

    bool loadApiKey();
    bool checkInternetAccess();
    void sendMessageAsync(const String& message, ResponseCallback callback,
                          const String& preset_json);
    void sendMessagesAsync(const StringArray& messages, ResponseCallback callback,
                           const String& preset_json);
    void routeMessageAsync(const String& message, RouterCallback callback);
    void sendSoundDesignTranslationAsync(const String& message, ResponseCallback callback,
                                          const String& preset_json);
    void addMessage(const String& role, const String& content);
    void logRequest(const String& endpoint_label, const String& request_body,
                    const String& response_body, const var& parsed_response);

    static const int kMaxMessages = 20;

    struct ChatMessage {
      String role;
      String content;
    };
    std::vector<ChatMessage> conversation_history_;

    bool loadSystemPrompt();
    bool loadPresetSchema();
    bool loadSoundDesignPrompt();
    bool loadCookbook();

    std::string api_key_path_;
    std::string api_key_;
    String system_prompt_;
    String preset_schema_;
    String sound_design_prompt_;
    bool initialized_ = false;
    bool internet_access_ = false;
};
