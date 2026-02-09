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
