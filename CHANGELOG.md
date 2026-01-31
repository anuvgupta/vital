# Vital project changelog

## Latest Updates

### More Details

- More details are in `TODO.md`


### Update List

- We drafted a document outlining the preset format/schema, based on the Vital codebase and some example presets: `agents/vital-assistant/PRESET_SCHEMA.md`
    - We learned that waveforms can be stored as "Wave Source" (base64, not really LLM-friendly) OR "Line Source" (control points / curves, very LLM-friendly). We will prefer line source for preset generation. We will deal with wave source later.
- We created a build script `build_macos.sh` because we are developing on MacOS. This runs Projucer CLI to build the project to MacOS (Xcode) and other targets. Then it uses Xcode CLI to run the debug app. We can use this script with `--no-run` argument to verify that new changes build/compile successfully.
- We added a sidepanel (via `side_panel.cpp`) where we will continue to add functionality
- We added a textarea and a button to the sidepanel, near the bottom
- We implemented a chat interface with scrollable message area, user message bubbles, and "Thinking..." indicator
- We added a menu option to save claude API key path in user settings (Vital json config stored in `Library/Application Support` or `APPDATA`, etc.) and load the path when the app starts
- We added an API client for Claude (Anthropic/Claude Platform API). The side panel initializes the API client with the API key (if exists), checks internet access, and adds a "Ready" message to the chat window.
- We implemented chat message sending to Claude API with background threading: user submits message -> sidepanel notifies listeners -> `FullInterface::sidePanelMessageSubmitted()` calls `ClaudeApiClient::sendMessage()` -> background thread makes HTTP POST -> response delivered via `MessageManager::callAsync()` back to UI thread
- We added persistent conversation history (max 20 messages) to ClaudeApiClient: each new message is added to history, the API sends full conversation context, and responses are stored for multi-turn dialogue
- We added a system prompt for the Vital AI assistant: `ClaudeApiClient` loads `SYSTEM_PROMPT.md` from the app bundle Resources dir (fallback to data dir), sent via the Anthropic API's top-level `"system"` field. The build script copies the prompt file into the bundle.
- We added current preset JSON injection to Claude API chat: when user sends a message, the synth preset is serialized to JSON and injected as a user message before the actual message. Base64 data (wave_data, samples) is stripped to save tokens.
- We switched from full preset JSON responses to a JSON diff/merge patch approach (RFC 7396 style): Claude returns only changed keys, which are recursively merged into the current preset via `mergeJson()`. This avoids token limits (full presets are 4000+ lines). Added `loadStateFromJson()` public wrapper on `SynthBase` to apply the merged result.
- We added cost control limits: API output tokens capped at 1024 (`kMaxTokens`), and user input messages truncated to 1024 characters before being added to conversation history (preset JSON context is not truncated).
- We added preset schema loading to ClaudeApiClient: `PRESET_SCHEMA.md` (documenting all parameters, value ranges, and scaling formulas like quadratic/exponential) is loaded at init and appended to the system prompt. This gives the AI assistant accurate knowledge of how to compute stored values from user-facing percentages (e.g., quadratic: stored = sqrt(UI_value)).
- We added markdown rendering for chat messages: vendored md4c (C markdown parser, MIT) in `third_party/md4c/`, created `markdown_parser.h/cpp` that parses markdown into `MarkdownBlock`/`StyledRun` structs via SAX callbacks, and updated `side_panel.cpp` to render paragraphs with bold/italic/mono, headings, fenced code blocks, bullet/numbered lists, block quotes, and horizontal rules. System messages are parsed as markdown; user messages stay plain text.
- We improved API response handling to support mixed text+JSON responses: the response parser extracts JSON from markdown code fences (``` blocks, including ` ```json ` indicators), applies preset diffs from the JSON, and displays surrounding text (before/after the fence) as a chat message. This allows the AI to explain changes alongside applying them. Added random whimsical completion phrases (`getCompletionPhrase()`) as fallback when no text accompanies a preset update. The extraction logic properly handles cases where the model returns both a message and a JSON update in a single response.
- We improved `mergeJson()` to handle wavetable arrays intelligently: array elements are now merged element-by-element (null means keep original), and placeholder strings like "(base64 data removed)" are skipped so the AI can't accidentally overwrite real base64 data with stripped placeholders.
