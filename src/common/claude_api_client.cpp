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
  const String kModelSonnet = "claude-sonnet-4-5-20241022";
  const String kModelOpus = "claude-opus-4-5-20251101";
  const String kModel = kModelOpus;
  const int kMaxTokens = 1024;
  const int kRouterMaxTokens = 512;
  const int kTimeoutMs = 30000;

  const String kRouterSystemPrompt =
    "You are a routing assistant for a synthesizer preset modification tool. "
    "Analyze the user's request and break it into atomic preset modification actions. "
    "Each action should be a single, self-contained instruction that can be executed independently. "
    "For simple requests (single parameter change, one effect toggle, a question), return a single action matching the original request. "
    "For complex multi-part requests (e.g. 'make a dark dubstep bass with wobble and distortion'), "
    "split into ordered steps where each step builds on the previous. "
    "For questions or non-modification requests, return the original request as a single action.";
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

  if (!loadSystemPrompt())
    DBG("ClaudeApiClient: Failed to load system prompt");

  if (!loadPresetSchema())
    DBG("ClaudeApiClient: Failed to load preset schema");
  else if (system_prompt_.isNotEmpty())
    system_prompt_ += "\n\n" + preset_schema_;

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

bool ClaudeApiClient::loadSystemPrompt() {
  // Look for SYSTEM_PROMPT.md relative to the executable or in known locations
  File executable = File::getSpecialLocation(File::currentExecutableFile);
  File prompt_file;

  // Try alongside the executable's bundle (macOS: Contents/MacOS/../Resources)
  File resources_dir = executable.getParentDirectory().getParentDirectory().getChildFile("Resources");
  prompt_file = resources_dir.getChildFile("SYSTEM_PROMPT.md");

  if (!prompt_file.existsAsFile()) {
    // Try same directory as executable (Windows: files copied next to .exe)
    prompt_file = executable.getParentDirectory().getChildFile("SYSTEM_PROMPT.md");
  }

  if (!prompt_file.existsAsFile()) {
    // Try the user's application data directory
    File app_data = LoadSave::getDataDirectory();
    prompt_file = app_data.getChildFile("SYSTEM_PROMPT.md");
  }

  if (!prompt_file.existsAsFile()) {
    DBG("ClaudeApiClient: System prompt file not found");
    return false;
  }

  system_prompt_ = prompt_file.loadFileAsString().trim();
  DBG("ClaudeApiClient: Loaded system prompt (" + String(system_prompt_.length()) + " chars)");
  return system_prompt_.isNotEmpty();
}

bool ClaudeApiClient::loadPresetSchema() {
  File executable = File::getSpecialLocation(File::currentExecutableFile);
  File prompt_file;

  File resources_dir = executable.getParentDirectory().getParentDirectory().getChildFile("Resources");
  prompt_file = resources_dir.getChildFile("PRESET_SCHEMA.md");

  if (!prompt_file.existsAsFile()) {
    // Try same directory as executable (Windows: files copied next to .exe)
    prompt_file = executable.getParentDirectory().getChildFile("PRESET_SCHEMA.md");
  }

  if (!prompt_file.existsAsFile()) {
    File app_data = LoadSave::getDataDirectory();
    prompt_file = app_data.getChildFile("PRESET_SCHEMA.md");
  }

  if (!prompt_file.existsAsFile()) {
    DBG("ClaudeApiClient: Preset schema file not found");
    return false;
  }

  preset_schema_ = prompt_file.loadFileAsString().trim();
  DBG("ClaudeApiClient: Loaded preset schema (" + String(preset_schema_.length()) + " chars)");
  return preset_schema_.isNotEmpty();
}

bool ClaudeApiClient::checkInternetAccess() {
  URL url("https://claude.ai");
  std::unique_ptr<InputStream> stream(url.createInputStream(false, nullptr, nullptr, "", 5000));
  return stream != nullptr;
}

void ClaudeApiClient::sendMessage(const String& message, ResponseCallback callback,
                                   const String& preset_json) {
  StringArray messages;
  messages.add(message);
  sendMessages(messages, callback, preset_json);
}

void ClaudeApiClient::sendMessages(const StringArray& messages, ResponseCallback callback,
                                    const String& preset_json) {
  if (!initialized_) {
    callback("API client not initialized. Please configure your API key.", false);
    return;
  }

  if (api_key_.empty()) {
    callback("API key not configured.", false);
    return;
  }

  // Run on background thread to avoid blocking UI
  Thread::launch([this, messages, callback, preset_json]() {
    sendMessagesAsync(messages, callback, preset_json);
  });
}

void ClaudeApiClient::clearConversation() {
  conversation_history_.clear();
}

void ClaudeApiClient::truncateHistoryTo(int size) {
  if (size >= 0 && size < (int)conversation_history_.size())
    conversation_history_.resize(size);
}

void ClaudeApiClient::extractFenceContent(const String& response, String& textOut, String& jsonOut) {
  textOut = String();
  jsonOut = String();

  int fenceStart = response.indexOf(String("```"));
  if (fenceStart < 0)
    return;

  textOut = response.substring(0, fenceStart).trim();

  int contentStart = response.substring(fenceStart).indexOf(String("\n"));
  if (contentStart < 0)
    return;

  contentStart += fenceStart + 1;
  int fenceEnd = response.substring(contentStart).indexOf(String("```"));
  if (fenceEnd < 0)
    return;

  fenceEnd += contentStart;
  jsonOut = response.substring(contentStart, fenceEnd).trim();

  String trailing = response.substring(fenceEnd + 3).trim();
  if (trailing.isNotEmpty()) {
    if (textOut.isNotEmpty())
      textOut += " ";
    textOut += trailing;
  }
}

void ClaudeApiClient::addMessage(const String& role, const String& content) {
  while (conversation_history_.size() >= kMaxMessages)
    conversation_history_.erase(conversation_history_.begin());

  conversation_history_.push_back({ role, content });
}

void ClaudeApiClient::sendMessageAsync(const String& message, ResponseCallback callback,
                                        const String& preset_json) {
  StringArray messages;
  messages.add(message);
  sendMessagesAsync(messages, callback, preset_json);
}

void ClaudeApiClient::sendMessagesAsync(const StringArray& messages, ResponseCallback callback,
                                         const String& preset_json) {
  // Add all user messages to conversation history (preset context is NOT stored — it's ephemeral)
  for (const auto& message : messages) {
    String truncated_message = message.length() > 1024 ? message.substring(0, 1024) : message;
    addMessage("user", truncated_message);
  }

  // Build the JSON request body
  DynamicObject::Ptr requestBody = new DynamicObject();
  requestBody->setProperty("model", kModel);
  requestBody->setProperty("max_tokens", kMaxTokens);

  if (system_prompt_.isNotEmpty()) {
    // Send system prompt as array with cache_control for prompt caching
    DynamicObject::Ptr cacheControl = new DynamicObject();
    cacheControl->setProperty("type", "ephemeral");
    cacheControl->setProperty("ttl", "1h");

    DynamicObject::Ptr systemBlock = new DynamicObject();
    systemBlock->setProperty("type", "text");
    systemBlock->setProperty("text", system_prompt_);
    systemBlock->setProperty("cache_control", var(cacheControl.get()));

    Array<var> systemArray;
    systemArray.add(var(systemBlock.get()));
    requestBody->setProperty("system", systemArray);
  }

  // Build messages array: prior turns from history, then preset context (ephemeral), then current turn
  int new_message_count = messages.size();
  int history_size = (int)conversation_history_.size();
  int prior_count = history_size - new_message_count;

  Array<var> messagesArray;

  // All prior-turn messages (no stale preset snapshots)
  for (int i = 0; i < prior_count; ++i) {
    const auto& msg = conversation_history_[i];
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
  }

  // Inject current preset context just before this turn's user message(s) — not stored in history
  if (preset_json.isNotEmpty()) {
    String preset_context = "This is the current preset JSON:\n```json\n" + preset_json + "\n```";
    DynamicObject::Ptr presetMsg = new DynamicObject();
    presetMsg->setProperty("role", "user");
    presetMsg->setProperty("content", preset_context);
    messagesArray.add(var(presetMsg.get()));
  }

  // Current turn's user message(s)
  for (int i = prior_count; i < history_size; ++i) {
    const auto& msg = conversation_history_[i];
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
  }

  requestBody->setProperty("messages", messagesArray);

  String jsonBody = JSON::toString(var(requestBody.get()));
  DBG("ClaudeApiClient: Sending request: " + jsonBody);

  // Build headers
  String headers = "x-api-key: " + String(api_key_) + "\r\n"
                   "anthropic-version: 2023-06-01\r\n"
                   "anthropic-beta: extended-cache-ttl-2025-04-11\r\n"
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

  // Store only the text portion in history — strip the JSON fence since the preset
  // state is always re-injected fresh at the start of each turn anyway.
  String textOnly, jsonOnly;
  extractFenceContent(responseText, textOnly, jsonOnly);
  addMessage("assistant", textOnly.isNotEmpty() ? textOnly : responseText);

  MessageManager::callAsync([callback, responseText]() {
    callback(responseText, true);
  });
}

void ClaudeApiClient::addToHistory(const String& role, const String& content) {
  addMessage(role, content);
}

void ClaudeApiClient::routeMessage(const String& message, RouterCallback callback) {
  if (!initialized_ || api_key_.empty()) {
    callback(StringArray(), false, "API client not initialized.");
    return;
  }

  Thread::launch([this, message, callback]() {
    routeMessageAsync(message, callback);
  });
}

void ClaudeApiClient::routeMessageAsync(const String& message, RouterCallback callback) {
  // Build request body
  DynamicObject::Ptr requestBody = new DynamicObject();
  requestBody->setProperty("model", kModel);
  requestBody->setProperty("max_tokens", kRouterMaxTokens);

  // System prompt
  {
    DynamicObject::Ptr systemBlock = new DynamicObject();
    systemBlock->setProperty("type", "text");
    systemBlock->setProperty("text", kRouterSystemPrompt);
    Array<var> systemArray;
    systemArray.add(var(systemBlock.get()));
    requestBody->setProperty("system", systemArray);
  }

  // Messages: conversation history (read-only, for context) + current user message
  Array<var> messagesArray;
  for (const auto& msg : conversation_history_) {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
  }

  // Current user message
  {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", "user");
    msgObj->setProperty("content", message);
    messagesArray.add(var(msgObj.get()));
  }
  requestBody->setProperty("messages", messagesArray);

  // Tool definition: route_actions
  {
    DynamicObject::Ptr actionItems = new DynamicObject();
    actionItems->setProperty("type", "string");

    DynamicObject::Ptr actionsProp = new DynamicObject();
    actionsProp->setProperty("type", "array");
    actionsProp->setProperty("items", var(actionItems.get()));
    actionsProp->setProperty("description", "Ordered list of atomic actions to execute sequentially");

    DynamicObject::Ptr properties = new DynamicObject();
    properties->setProperty("actions", var(actionsProp.get()));

    Array<var> required;
    required.add("actions");

    DynamicObject::Ptr inputSchema = new DynamicObject();
    inputSchema->setProperty("type", "object");
    inputSchema->setProperty("properties", var(properties.get()));
    inputSchema->setProperty("required", required);

    DynamicObject::Ptr tool = new DynamicObject();
    tool->setProperty("name", "route_actions");
    tool->setProperty("description", "Route user request into sequential preset modification actions");
    tool->setProperty("input_schema", var(inputSchema.get()));

    Array<var> toolsArray;
    toolsArray.add(var(tool.get()));
    requestBody->setProperty("tools", toolsArray);
  }

  // Force tool use
  {
    DynamicObject::Ptr toolChoice = new DynamicObject();
    toolChoice->setProperty("type", "tool");
    toolChoice->setProperty("name", "route_actions");
    requestBody->setProperty("tool_choice", var(toolChoice.get()));
  }

  String jsonBody = JSON::toString(var(requestBody.get()));
  DBG("ClaudeApiClient::routeMessage: Sending request: " + jsonBody);

  // Build headers
  String headers = "x-api-key: " + String(api_key_) + "\r\n"
                   "anthropic-version: 2023-06-01\r\n"
                   "content-type: application/json";

  URL url(kApiEndpoint);
  url = url.withPOSTData(jsonBody);

  std::unique_ptr<InputStream> stream(url.createInputStream(
    true, nullptr, nullptr, headers, kTimeoutMs, nullptr, nullptr, 0, "POST"
  ));

  if (!stream) {
    MessageManager::callAsync([callback]() {
      callback(StringArray(), false, "Failed to connect to Claude API.");
    });
    return;
  }

  String response = stream->readEntireStreamAsString();
  DBG("ClaudeApiClient::routeMessage: Response: " + response);

  var parsedResponse = JSON::parse(response);
  if (!parsedResponse.isObject()) {
    MessageManager::callAsync([callback]() {
      callback(StringArray(), false, "Failed to parse router API response.");
    });
    return;
  }

  if (parsedResponse.hasProperty("error")) {
    var error = parsedResponse["error"];
    String errorMessage = error.isObject() && error.hasProperty("message")
      ? error["message"].toString() : "Router API error";
    MessageManager::callAsync([callback, errorMessage]() {
      callback(StringArray(), false, errorMessage);
    });
    return;
  }

  // Parse tool_use response: find content block with type "tool_use"
  var content = parsedResponse["content"];
  if (!content.isArray()) {
    MessageManager::callAsync([callback]() {
      callback(StringArray(), false, "Unexpected router response format.");
    });
    return;
  }

  for (int i = 0; i < content.size(); ++i) {
    var block = content[i];
    if (block.isObject() && block["type"].toString() == "tool_use") {
      var input = block["input"];
      if (input.isObject() && input.hasProperty("actions")) {
        var actionsVar = input["actions"];
        if (actionsVar.isArray()) {
          StringArray actions;
          for (int j = 0; j < actionsVar.size(); ++j)
            actions.add(actionsVar[j].toString());

          if (actions.isEmpty()) {
            MessageManager::callAsync([callback]() {
              callback(StringArray(), false, "Router returned empty actions.");
            });
          } else {
            MessageManager::callAsync([callback, actions]() {
              callback(actions, true, String());
            });
          }
          return;
        }
      }
    }
  }

  // No tool_use block found
  MessageManager::callAsync([callback]() {
    callback(StringArray(), false, "Router did not return expected tool_use response.");
  });
}
