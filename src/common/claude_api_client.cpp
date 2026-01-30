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
