# Documenter Agent's Long-Term Memory

## Architectural Patterns in Vital

### UI Listener Pattern
- UI sections (like VitalSidePanel) define inner `Listener` classes with pure virtual callbacks
- Parent components (like FullInterface) inherit from these Listeners and implement callbacks
- Registration via `addListener(this)` in parent's constructor
- This decouples UI components from business logic (API calls, preset manipulation, etc.)

### API Client Pattern
- ClaudeApiClient uses singleton pattern via `instance()` static method
- Initialization separate from construction (call `initialize()` after settings are loaded)
- HTTP requests run on background thread, callbacks delivered to UI thread via MessageManager

### Third-Party Library Vendoring Pattern
- Libraries vendored under `third_party/` (md4c, ixwebsocket)
- Added to jucer as source files (with compile="0" for unity build inclusion, or compile="1" for independent compilation)
- For libraries with ObjC dependencies or namespace conflicts, keep files outside unity builds

### macOS Permissions Pattern
- Hardened runtime requires explicit entitlements for hardware access (mic, camera, etc.)
- Set via `hardenedRuntimeOptions` in vital.jucer; Projucer generates the .entitlements file
- Permission requests must use ObjC APIs (AVCaptureDevice) in separate .mm files to avoid JUCE conflicts
- API key paths stored in Vital's JSON config (Library/Application Support) via LoadSave helper methods

### Voice Input Architecture
- DeepgramClient: singleton, PIMPL pattern to hide IXWebSocket headers from unity build
- MicrophoneCapture: separate AudioDeviceManager (1 in, 0 out) to isolate from synth audio
- Real-time flow: mic -> 16kHz resample -> WebSocket stream -> Deepgram Nova-3 -> interim/final transcripts -> side panel text editor -> auto-submit on endpointing or manual stop
- TLS backends are per-platform: Apple Secure Transport (macOS), mbedTLS 3.6.5 (Windows)
- Platform defines go in per-exporter extraDefs in vital.jucer, NOT project-level defines
- ix::initNetSystem() required on Windows (WSAStartup); called in DeepgramClient::initialize()
- Never include IXNetSystem.h in unity build files; use forward declarations to avoid Windows header min/max macro pollution

### Checkpoint/Autosave Pattern
- Checkpoints are saved as full .vital preset files to disk, indexed by message position in the chat
- `ChatCheckpoint` struct in `side_panel.h` holds filepath + message index
- Restore maps user message index to next system message's checkpoint (post-AI state)
- `ClaudeApiClient::truncateHistoryTo(int)` trims conversation history to match UI truncation
- SVG icons can be embedded as string literals in `paths.h` using `fromSvgData()` -- avoids BinaryData regeneration
- MSVC quirk: `vector::resize()` instantiates default constructor even when only shrinking; use `erase()` for types without default constructors
- **Checkpoint file lifecycle invariant**: checkpoint files on disk must only be deleted when the in-memory checkpoint object is permanently removed (not during edit-mode restore where cancel may need to resurrect it). Use `delete_files=false` when removing checkpoints that may be restored by cancel. `exitEditMode()` handles orphan cleanup by diffing snapshot vs current state.
- Edit mode state must be reset on ALL exit paths: submitMessage, processRecordedSpeech, clearChat, cancelEditMode. Missing any path leaves `edit_mode_=true` blocking future enterEditMode calls.

### Multi-Layer Router Pattern
- User message → router call (Claude tool_use, lightweight, no preset schema) → action list
- Router response contains `tool_use` block with `input.actions` array (forced via `tool_choice`)
- Single action: pass through to existing preset generation (no latency penalty perceived)
- Multiple actions: orchestrate via `routeAndExecute()` → `executeNextAction()` chain
- Each sub-action is added to conversation history manually via `ClaudeApiClient::addToHistory()` so LLM sees context
- Status messages ("Breaking it down...", "Step 1/3...", etc) replace last system message via `VitalSidePanel::updateStatusMessage()`
- Router system prompt tuned to batch simple independent changes and minimize splitting (most real requests = 1 action)
- ChatMessage stores both `text` and `blocks` (parsed markdown) — updating text requires re-parsing: `message.blocks = parseMarkdown(text)`
- Third router path: `sound_design_required` boolean in tool schema detects non-technical descriptions
- Sound design translation uses separate system prompt (SOUND_DESIGN_PROMPT.md) + cookbook, NOT the main system prompt
- Translation output is NOT stored in conversation history — it's an internal intermediate step
- After translation, output is re-routed through routeAndExecute() which splits into sub-actions
- Infinite loop guard: `is_sound_design_reroute_` flag on FullInterface prevents re-triggering sound design path
- kMaxTokens must be large enough (4096) for preset generation JSON diffs; truncated JSON causes raw text display in chat
- Resource files (SOUND_DESIGN_PROMPT.md, SOUND_DESIGN_GUIDE.md) must be copied by ALL platform build scripts

### API Cost Analysis Pattern
- Request logs can be analyzed from `api_requests.log` in user data directory (added via `logRequest()` method)
- 3 request tiers by token count: sound design (~90-95k), standard preset mods (~27-32k), router (~1-5k)
- All conversation history writes go through `addMessage()` — only 3 call sites exist in the codebase (2 in claude_api_client.cpp, 1 in full_interface.cpp)
- Token cost is dominated by uncached input tokens (~70% of total cost); prompt caching helps but conversation history and preset JSON are per-request
- The 296KB SYNTHESIZER_COOKBOOK was the single largest token contributor per sound design call; was renamed to SOUND_DESIGN_GUIDE.md and emptied, needs a compact replacement
- Router calls are cheap (~1-5k tokens) and can use Sonnet instead of Opus since they only classify via tool_use with ~50-100 output tokens

### Async Callback Invalidation Pattern
- Generation counter (`api_request_generation_`) on FullInterface invalidates in-flight async callbacks
- Pattern: capture counter before lambda, check inside lambda, bump counter at invalidation points
- Invalidation points: sidePanelRestoreRequested(), sidePanelCancelEditRequested()
- Applies to: routeAndExecute() router callback, sound design translation callback, sendApiRequest() callback
- This pattern is reusable anywhere async work can be superseded by user state changes

### JSON Response Handling Pattern
- LLM can return preset JSON in 3 formats: pure JSON (no fences), fenced JSON (markdown code block), inline JSON (text + unbraced JSON)
- `splitResponseText()` in ClaudeApiClient detects all 3: checks if trimmed response starts with `{`, looks for ```json fence, then searches for `{"settings"` substring
- Only the text portion (before/after JSON) should be stored in conversation history; the JSON is applied via mergeJson() and discarded
- Failing to strip JSON from history on all 3 formats causes conversation pollution (raw JSON in subsequent prompts), token waste, and confuses multi-action flows
- Renaming functions when scope expands beyond original name prevents future bugs where developers assume old behavior based on name
