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
  const String kModelSonnet = "claude-sonnet-4-5-20250929";
  const String kModelOpus = "claude-opus-4-5-20251101";
  const String kModel = kModelOpus;
  const int kMaxTokens = 4096;
  const int kRouterMaxTokens = 512;
  const int kSoundDesignMaxTokens = 1024;
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

  if (!loadSystemPrompt())
    DBG("ClaudeApiClient: Failed to load system prompt");

  if (!loadPresetSchema())
    DBG("ClaudeApiClient: Failed to load preset schema");
  else if (system_prompt_.isNotEmpty())
    system_prompt_ += "\n\n" + preset_schema_;

  if (!loadRouterPrompt())
    DBG("ClaudeApiClient: Failed to load router prompt");

  if (!loadSoundDesignPrompt())
    DBG("ClaudeApiClient: Failed to load sound design prompt");
  else
    loadCookbook();  // Appends cookbook to sound_design_prompt_

  internet_access_ = checkInternetAccess();
  if (!internet_access_)
    DBG("ClaudeApiClient: No internet access detected");

  rotateRequestLog();

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

bool ClaudeApiClient::loadRouterPrompt() {
  File executable = File::getSpecialLocation(File::currentExecutableFile);
  File prompt_file;

  File resources_dir = executable.getParentDirectory().getParentDirectory().getChildFile("Resources");
  prompt_file = resources_dir.getChildFile("ROUTER_PROMPT.md");

  if (!prompt_file.existsAsFile())
    prompt_file = executable.getParentDirectory().getChildFile("ROUTER_PROMPT.md");

  if (!prompt_file.existsAsFile()) {
    File app_data = LoadSave::getDataDirectory();
    prompt_file = app_data.getChildFile("ROUTER_PROMPT.md");
  }

  if (!prompt_file.existsAsFile()) {
    DBG("ClaudeApiClient: Router prompt file not found");
    return false;
  }

  router_prompt_ = prompt_file.loadFileAsString().trim();
  DBG("ClaudeApiClient: Loaded router prompt (" + String(router_prompt_.length()) + " chars)");
  return router_prompt_.isNotEmpty();
}

bool ClaudeApiClient::loadSoundDesignPrompt() {
  File executable = File::getSpecialLocation(File::currentExecutableFile);
  File prompt_file;

  File resources_dir = executable.getParentDirectory().getParentDirectory().getChildFile("Resources");
  prompt_file = resources_dir.getChildFile("SOUND_DESIGN_PROMPT.md");

  if (!prompt_file.existsAsFile())
    prompt_file = executable.getParentDirectory().getChildFile("SOUND_DESIGN_PROMPT.md");

  if (!prompt_file.existsAsFile()) {
    File app_data = LoadSave::getDataDirectory();
    prompt_file = app_data.getChildFile("SOUND_DESIGN_PROMPT.md");
  }

  if (!prompt_file.existsAsFile()) {
    DBG("ClaudeApiClient: Sound design prompt file not found");
    return false;
  }

  sound_design_prompt_ = prompt_file.loadFileAsString().trim();
  DBG("ClaudeApiClient: Loaded sound design prompt (" + String(sound_design_prompt_.length()) + " chars)");
  return sound_design_prompt_.isNotEmpty();
}

bool ClaudeApiClient::loadCookbook() {
  File executable = File::getSpecialLocation(File::currentExecutableFile);
  File cookbook_file;

  File resources_dir = executable.getParentDirectory().getParentDirectory().getChildFile("Resources");
  cookbook_file = resources_dir.getChildFile("SOUND_DESIGN_GUIDE.md");

  if (!cookbook_file.existsAsFile())
    cookbook_file = executable.getParentDirectory().getChildFile("SOUND_DESIGN_GUIDE.md");

  if (!cookbook_file.existsAsFile()) {
    File app_data = LoadSave::getDataDirectory();
    cookbook_file = app_data.getChildFile("SOUND_DESIGN_GUIDE.md");
  }

  if (!cookbook_file.existsAsFile()) {
    DBG("ClaudeApiClient: Synthesizer cookbook file not found");
    return false;
  }

  String cookbook = cookbook_file.loadFileAsString().trim();
  DBG("ClaudeApiClient: Loaded synthesizer cookbook (" + String(cookbook.length()) + " chars)");

  if (cookbook.isNotEmpty() && sound_design_prompt_.isNotEmpty())
    sound_design_prompt_ += "\n\n" + cookbook;

  return cookbook.isNotEmpty();
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

std::vector<ClaudeApiClient::HistoryEntry> ClaudeApiClient::getHistorySnapshot() const {
  std::vector<HistoryEntry> snapshot;
  snapshot.reserve(conversation_history_.size());
  for (const auto& msg : conversation_history_)
    snapshot.push_back({ msg.role, msg.content });
  return snapshot;
}

void ClaudeApiClient::restoreHistory(const std::vector<HistoryEntry>& snapshot) {
  conversation_history_.clear();
  conversation_history_.reserve(snapshot.size());
  for (const auto& entry : snapshot)
    conversation_history_.push_back({ entry.role, entry.content });
}


void ClaudeApiClient::splitResponseText(const String& response, String& textOut, String& jsonOut) {
  textOut = String();
  jsonOut = String();

  // --- Case 2: code fences ---
  int fenceStart = response.indexOf(String("```"));
  if (fenceStart >= 0) {
    textOut = response.substring(0, fenceStart).trim();

    int contentStart = response.substring(fenceStart).indexOf(String("\n"));
    if (contentStart < 0)
      return;

    contentStart += fenceStart + 1;
    int fenceEnd = response.substring(contentStart).indexOf(String("```"));
    if (fenceEnd < 0) {
      jsonOut = response.substring(contentStart).trim();
      return;
    }

    fenceEnd += contentStart;
    jsonOut = response.substring(contentStart, fenceEnd).trim();

    String trailing = response.substring(fenceEnd + 3).trim();
    if (trailing.isNotEmpty()) {
      if (textOut.isNotEmpty())
        textOut += " ";
      textOut += trailing;
    }
    return;
  }

  // --- No fences found — check for raw/inline JSON ---
  String trimmed = response.trim();

  // Case 1: pure raw JSON (starts with '{')
  if (trimmed.startsWith("{")) {
    jsonOut = trimmed;
    return;
  }

  // Case 3: text followed by inline JSON without fences
  int jsonStart = response.indexOf("{\"settings\"");
  if (jsonStart < 0)
    jsonStart = response.indexOf("{\n\"settings\"");
  if (jsonStart > 0) {
    textOut = response.substring(0, jsonStart).trim();
    jsonOut = response.substring(jsonStart).trim();
  }
}

void ClaudeApiClient::addMessage(const String& role, const String& content) {
  while (conversation_history_.size() >= kMaxMessages)
    conversation_history_.erase(conversation_history_.begin());

  conversation_history_.push_back({ role, content });
}

void ClaudeApiClient::rotateRequestLog() {
  File logs_dir = LoadSave::getDataDirectory().getChildFile("logs");
  if (!logs_dir.isDirectory())
    return;

  File current_log = logs_dir.getChildFile("api_requests_current.log");
  if (!current_log.existsAsFile() || current_log.getSize() == 0)
    return;

  int highest = 0;
  for (const auto& f : logs_dir.findChildFiles(File::findFiles, false, "api_requests_*.log")) {
    String name = f.getFileNameWithoutExtension(); // e.g. "api_requests_3"
    if (name == "api_requests_current")
      continue;
    String suffix = name.fromLastOccurrenceOf("api_requests_", false, false);
    int n = suffix.getIntValue();
    if (n > highest)
      highest = n;
  }

  File dest = logs_dir.getChildFile("api_requests_" + String(highest + 1) + ".log");
  current_log.moveFileTo(dest);
}

void ClaudeApiClient::logRequest(const String& endpoint_label, const String& request_body,
                                  const String& response_body, const var& parsed_response) {
  File logs_dir = LoadSave::getDataDirectory().getChildFile("logs");
  logs_dir.createDirectory();
  File log_file = logs_dir.getChildFile("api_requests_current.log");

  String timestamp = Time::getCurrentTime().toISO8601(true);

  String usage_info;
  if (parsed_response.isObject() && parsed_response.hasProperty("usage")) {
    var usage = parsed_response["usage"];
    int input_tokens = usage.getProperty("input_tokens", 0);
    int output_tokens = usage.getProperty("output_tokens", 0);
    int cache_read = usage.getProperty("cache_read_input_tokens", 0);
    int cache_create = usage.getProperty("cache_creation_input_tokens", 0);
    usage_info = " | input_tokens=" + String(input_tokens)
               + " output_tokens=" + String(output_tokens)
               + " cache_read=" + String(cache_read)
               + " cache_create=" + String(cache_create);
  }

  String log_entry = "--- " + timestamp + " | " + endpoint_label + " ---\n"
                   + "REQUEST_CHARS=" + String(request_body.length())
                   + " RESPONSE_CHARS=" + String(response_body.length())
                   + usage_info + "\n"
                   + "REQUEST:\n" + request_body + "\n"
                   + "RESPONSE:\n" + response_body + "\n\n";

  log_file.appendText(log_entry);
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

  // Build single user message: history context + preset state + current request
  int new_message_count = messages.size();
  int history_size = (int)conversation_history_.size();
  int prior_count = history_size - new_message_count;

  String userMessage;

  // Conversation history as context block
  if (prior_count > 0) {
    userMessage += "<conversation_history>\n";
    for (int i = 0; i < prior_count; ++i) {
      const auto& msg = conversation_history_[i];
      userMessage += msg.role + ": " + msg.content + "\n";
    }
    userMessage += "</conversation_history>\n\n";
  }

  // Current preset state
  if (preset_json.isNotEmpty())
    userMessage += "<current_preset>\n" + preset_json + "\n</current_preset>\n\n";

  // Current request
  userMessage += "<current_request>\n";
  for (int i = prior_count; i < history_size; ++i)
    userMessage += conversation_history_[i].content + "\n";
  userMessage += "</current_request>";

  Array<var> messagesArray;
  {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", "user");
    msgObj->setProperty("content", userMessage);
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
  logRequest("sendMessage", jsonBody, response, parsedResponse);

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

  // Store only the text portion in history — skip pure preset updates since the
  // preset state is always re-injected fresh at the start of each turn anyway.
  String textOnly, jsonOnly;
  splitResponseText(responseText, textOnly, jsonOnly);
  if (jsonOnly.isNotEmpty())
    addMessage("assistant", textOnly.isNotEmpty() ? textOnly : String("Done."));
  else
    addMessage("assistant", responseText);

  MessageManager::callAsync([callback, responseText]() {
    callback(responseText, true);
  });
}

void ClaudeApiClient::addToHistory(const String& role, const String& content) {
  addMessage(role, content);
}

void ClaudeApiClient::routeMessage(const String& message, RouterCallback callback) {
  if (!initialized_ || api_key_.empty()) {
    callback(StringArray(), false, false, String(), false, "API client not initialized.");
    return;
  }

  Thread::launch([this, message, callback]() {
    routeMessageAsync(message, callback);
  });
}

void ClaudeApiClient::routeMessageAsync(const String& message, RouterCallback callback) {
  // Build request body — use Sonnet for routing (cheaper, sufficient for classification)
  DynamicObject::Ptr requestBody = new DynamicObject();
  requestBody->setProperty("model", kModelSonnet);
  requestBody->setProperty("max_tokens", kRouterMaxTokens);

  // System prompt
  {
    DynamicObject::Ptr systemBlock = new DynamicObject();
    systemBlock->setProperty("type", "text");
    systemBlock->setProperty("text", router_prompt_);
    Array<var> systemArray;
    systemArray.add(var(systemBlock.get()));
    requestBody->setProperty("system", systemArray);
  }

  // Build single user message with history context + current request
  String userMessage;
  if (!conversation_history_.empty()) {
    userMessage += "<conversation_history>\n";
    for (const auto& msg : conversation_history_)
      userMessage += msg.role + ": " + msg.content + "\n";
    userMessage += "</conversation_history>\n\n";
  }
  userMessage += "<current_request>\n" + message + "\n</current_request>";

  Array<var> messagesArray;
  {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", "user");
    msgObj->setProperty("content", userMessage);
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
    actionsProp->setProperty("description", "Ordered list of actions. Empty when sound_design_required is true.");

    DynamicObject::Ptr soundDesignProp = new DynamicObject();
    soundDesignProp->setProperty("type", "boolean");
    soundDesignProp->setProperty("description",
      "Set to true when the user describes a sound non-technically (vibe, texture, genre, instrument) "
      "rather than specific parameters. When true, actions should be empty.");

    DynamicObject::Ptr saveRequiredProp = new DynamicObject();
    saveRequiredProp->setProperty("type", "boolean");
    saveRequiredProp->setProperty("description",
      "Set to true when the user explicitly asks to save the preset, or when the conversation "
      "context clearly implies they want to keep/store the current sound. Default false.");

    DynamicObject::Ptr presetNameProp = new DynamicObject();
    presetNameProp->setProperty("type", "string");
    presetNameProp->setProperty("description",
      "A short, descriptive preset name derived from the conversation context "
      "(e.g. 'Warm Analog Pad', 'Dirty 808 Bass'). Required when save_required is true, empty string otherwise.");

    DynamicObject::Ptr properties = new DynamicObject();
    properties->setProperty("actions", var(actionsProp.get()));
    properties->setProperty("sound_design_required", var(soundDesignProp.get()));
    properties->setProperty("save_required", var(saveRequiredProp.get()));
    properties->setProperty("preset_name", var(presetNameProp.get()));

    Array<var> required;
    required.add("actions");
    required.add("sound_design_required");
    required.add("save_required");
    required.add("preset_name");

    DynamicObject::Ptr inputSchema = new DynamicObject();
    inputSchema->setProperty("type", "object");
    inputSchema->setProperty("properties", var(properties.get()));
    inputSchema->setProperty("required", required);

    DynamicObject::Ptr tool = new DynamicObject();
    tool->setProperty("name", "route_actions");
    tool->setProperty("description", "Route user request: either into sequential actions or flag for sound design translation");
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
      callback(StringArray(), false, false, String(), false, "Failed to connect to Claude API.");
    });
    return;
  }

  String response = stream->readEntireStreamAsString();
  DBG("ClaudeApiClient::routeMessage: Response: " + response);

  var parsedResponse = JSON::parse(response);
  logRequest("routeMessage", jsonBody, response, parsedResponse);

  if (!parsedResponse.isObject()) {
    MessageManager::callAsync([callback]() {
      callback(StringArray(), false, false, String(), false, "Failed to parse router API response.");
    });
    return;
  }

  if (parsedResponse.hasProperty("error")) {
    var error = parsedResponse["error"];
    String errorMessage = error.isObject() && error.hasProperty("message")
      ? error["message"].toString() : "Router API error";
    MessageManager::callAsync([callback, errorMessage]() {
      callback(StringArray(), false, false, String(), false, errorMessage);
    });
    return;
  }

  // Parse tool_use response: find content block with type "tool_use"
  var content = parsedResponse["content"];
  if (!content.isArray()) {
    MessageManager::callAsync([callback]() {
      callback(StringArray(), false, false, String(), false, "Unexpected router response format.");
    });
    return;
  }

  for (int i = 0; i < content.size(); ++i) {
    var block = content[i];
    if (block.isObject() && block["type"].toString() == "tool_use") {
      var input = block["input"];
      if (input.isObject()) {
        // Extract sound_design_required flag
        bool soundDesignRequired = false;
        if (input.hasProperty("sound_design_required"))
          soundDesignRequired = (bool)input["sound_design_required"];

        // Extract save_required and preset_name
        bool saveRequired = false;
        String presetName;
        if (input.hasProperty("save_required"))
          saveRequired = (bool)input["save_required"];
        if (input.hasProperty("preset_name"))
          presetName = input["preset_name"].toString();

        if (soundDesignRequired) {
          // Sound design path — no actions needed
          MessageManager::callAsync([callback, saveRequired, presetName]() {
            callback(StringArray(), true, saveRequired, presetName, true, String());
          });
          return;
        }

        // Normal path — extract actions
        if (input.hasProperty("actions")) {
          var actionsVar = input["actions"];
          if (actionsVar.isArray()) {
            StringArray actions;
            for (int j = 0; j < actionsVar.size(); ++j)
              actions.add(actionsVar[j].toString());

            if (actions.isEmpty()) {
              if (saveRequired) {
                // Save-only request — no actions, just save
                MessageManager::callAsync([callback, presetName]() {
                  callback(StringArray(), false, true, presetName, true, String());
                });
              } else {
                MessageManager::callAsync([callback]() {
                  callback(StringArray(), false, false, String(), false, "Router returned empty actions.");
                });
              }
            } else {
              MessageManager::callAsync([callback, actions, saveRequired, presetName]() {
                callback(actions, false, saveRequired, presetName, true, String());
              });
            }
            return;
          }
        }
      }
    }
  }

  // No tool_use block found
  MessageManager::callAsync([callback]() {
    callback(StringArray(), false, false, String(), false, "Router did not return expected tool_use response.");
  });
}

void ClaudeApiClient::sendSoundDesignTranslation(const String& message, ResponseCallback callback,
                                                   const String& preset_json) {
  if (!initialized_ || api_key_.empty()) {
    callback("API client not initialized.", false);
    return;
  }

  Thread::launch([this, message, callback, preset_json]() {
    sendSoundDesignTranslationAsync(message, callback, preset_json);
  });
}

void ClaudeApiClient::sendSoundDesignTranslationAsync(const String& message, ResponseCallback callback,
                                                        const String& preset_json) {
  // NOTE: Do NOT add to conversation history here — the translation is an internal
  // intermediate step. The original user message will be stored by the re-routed flow.

  // Build the JSON request body
  DynamicObject::Ptr requestBody = new DynamicObject();
  requestBody->setProperty("model", kModel);
  requestBody->setProperty("max_tokens", kSoundDesignMaxTokens);

  if (sound_design_prompt_.isNotEmpty()) {
    DynamicObject::Ptr cacheControl = new DynamicObject();
    cacheControl->setProperty("type", "ephemeral");
    cacheControl->setProperty("ttl", "1h");

    DynamicObject::Ptr systemBlock = new DynamicObject();
    systemBlock->setProperty("type", "text");
    systemBlock->setProperty("text", sound_design_prompt_);
    systemBlock->setProperty("cache_control", var(cacheControl.get()));

    Array<var> systemArray;
    systemArray.add(var(systemBlock.get()));
    requestBody->setProperty("system", systemArray);
  }

  // Build messages array: full history for context, then preset context, then current message
  // (message is NOT in history — we pass it directly)
  Array<var> messagesArray;

  for (const auto& msg : conversation_history_) {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
  }

  // Inject current preset context
  if (preset_json.isNotEmpty()) {
    String preset_context = "This is the current preset JSON:\n```json\n" + preset_json + "\n```";
    DynamicObject::Ptr presetMsg = new DynamicObject();
    presetMsg->setProperty("role", "user");
    presetMsg->setProperty("content", preset_context);
    messagesArray.add(var(presetMsg.get()));
  }

  // Current turn's user message (not stored in history)
  {
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", "user");
    msgObj->setProperty("content", message);
    messagesArray.add(var(msgObj.get()));
  }

  requestBody->setProperty("messages", messagesArray);

  String jsonBody = JSON::toString(var(requestBody.get()));
  DBG("ClaudeApiClient::sendSoundDesignTranslation: Sending request: " + jsonBody);

  String headers = "x-api-key: " + String(api_key_) + "\r\n"
                   "anthropic-version: 2023-06-01\r\n"
                   "anthropic-beta: extended-cache-ttl-2025-04-11\r\n"
                   "content-type: application/json";

  URL url(kApiEndpoint);
  url = url.withPOSTData(jsonBody);

  std::unique_ptr<InputStream> stream(url.createInputStream(
    true, nullptr, nullptr, headers, kTimeoutMs, nullptr, nullptr, 0, "POST"
  ));

  if (!stream) {
    MessageManager::callAsync([callback]() {
      callback("Failed to connect to Claude API.", false);
    });
    return;
  }

  String response = stream->readEntireStreamAsString();
  DBG("ClaudeApiClient::sendSoundDesignTranslation: Response: " + response);

  var parsedResponse = JSON::parse(response);
  logRequest("soundDesignTranslation", jsonBody, response, parsedResponse);

  if (!parsedResponse.isObject()) {
    MessageManager::callAsync([callback]() {
      callback("Failed to parse API response.", false);
    });
    return;
  }

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

  // Do NOT store in history — translation is an internal intermediate step

  MessageManager::callAsync([callback, responseText]() {
    callback(responseText, true);
  });
}
