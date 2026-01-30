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

class ClaudeApiClient {
  public:
    using ResponseCallback = std::function<void(const String& response, bool success)>;

    static ClaudeApiClient& instance();

    bool initialize();
    bool isInitialized() const { return initialized_; }
    bool hasInternetAccess() const { return internet_access_; }
    const std::string& getApiKey() const { return api_key_; }
    const std::string& getApiKeyPath() const { return api_key_path_; }

    void sendMessage(const String& message, ResponseCallback callback);

  private:
    ClaudeApiClient();
    ~ClaudeApiClient() = default;
    ClaudeApiClient(const ClaudeApiClient&) = delete;
    ClaudeApiClient& operator=(const ClaudeApiClient&) = delete;

    bool loadApiKey();
    bool checkInternetAccess();
    void sendMessageAsync(const String& message, ResponseCallback callback);

    std::string api_key_path_;
    std::string api_key_;
    bool initialized_ = false;
    bool internet_access_ = false;
};
