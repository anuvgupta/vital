# Voice-to-Text for AI Chatbot Side Panel

## Context
The Vital synth has an AI chatbot side panel where users type text descriptions of sounds/parameter changes. We're adding voice input so users can speak instructions instead of typing. Uses Deepgram's WebSocket streaming API for real-time speech-to-text with automatic pause detection, then feeds transcripts into the existing chat message flow.

## Architecture Overview

```
[MIC button toggle] → [MicrophoneCapture] → PCM audio → [DeepgramClient WebSocket] → transcript
                                                                                         ↓
                                                              existing sidePanelMessageSubmitted() flow
```

## Key Decisions
- **WebSocket streaming** (not REST) for real-time transcription with Deepgram's built-in endpointing
- **Toggle button** next to COOK button (click to start/stop, auto-sends on pause)
- **IXWebSocket** library for WebSocket+TLS support (BSD license, no Boost, uses macOS SecureTransport)
- **Separate AudioDeviceManager** for mic input (doesn't interfere with synth audio output)
- **Deepgram API key** stored via same file-path-in-config pattern as Claude API key

---

## New Files

### 1. `third_party/ixwebsocket/` — Vendored WebSocket library
- Download IXWebSocket source (~15-20 files). BSD license, cross-platform, built-in TLS via macOS SecureTransport.
- Add source files with `compile="1"` in jucer (direct compilation like md4c), not via unity build.
- Add `../../../third_party/ixwebsocket` to header search paths.

### 2. `src/common/deepgram_client.h` / `deepgram_client.cpp` — Deepgram WebSocket client
- **Singleton** mirroring `ClaudeApiClient::instance()` pattern.
- `initialize()` — loads API key from `LoadSave::getDeepgramApiKeyPath()`, reads file contents.
- `connect(TranscriptCallback, ErrorCallback)` — opens WebSocket to `wss://api.deepgram.com/v1/listen?encoding=linear16&sample_rate=16000&channels=1&model=nova-3&endpointing=1500&utterance_end_ms=2000&interim_results=true&smart_format=true`
- Auth: `Authorization: Token <key>` header during WebSocket handshake.
- `sendAudioData(const void* data, int numBytes)` — sends raw PCM bytes as WebSocket binary frame.
- `disconnect()` — closes WebSocket cleanly.
- **Response parsing**: JSON messages from Deepgram. When `speech_final: true` or `UtteranceEnd` message type received, accumulates final transcript and calls `TranscriptCallback` on message thread via `MessageManager::callAsync()`.
- Uses PIMPL pattern to hide IXWebSocket from the header.
- Add `#include "deepgram_client.cpp"` to `src/unity_build/common.cpp`.

### 3. `src/common/microphone_capture.h` / `microphone_capture.cpp` — Mic audio capture
- Owns a dedicated `AudioDeviceManager` (1 input channel, 0 outputs).
- Implements `AudioIODeviceCallback` to receive float PCM from mic.
- In `audioDeviceIOCallback()`:
  - Downsample from device rate (typically 44100/48000) to 16000 Hz using `juce::LagrangeInterpolator`.
  - Convert float → int16 (linear16): `int16_t(sample * 32767.0f)`.
  - Pass converted buffer to callback: `AudioDataCallback(const void* data, int numBytes)`.
- `startCapture(AudioDataCallback)` / `stopCapture()` / `isCapturing()`.
- Pre-allocate conversion buffers to avoid audio-thread allocations.
- Add `#include "microphone_capture.cpp"` to `src/unity_build/common.cpp`.

---

## Modified Files

### 4. `src/interface/editor_sections/side_panel.h`
Add members:
```cpp
std::unique_ptr<OpenGlToggleButton> mic_button_;
std::unique_ptr<MicrophoneCapture> mic_capture_;
std::unique_ptr<OpenGlQuad> recording_indicator_;  // red dot
bool recording_ = false;
```
Add methods:
```cpp
void toggleRecording();
void startRecording();
void stopRecording();
void initializeDeepgramClient();
```

### 5. `src/interface/editor_sections/side_panel.cpp`
- **Constructor**: Pre-allocate `mic_button_` (OpenGlToggleButton "MIC"), `mic_capture_`, `recording_indicator_` (OpenGlQuad with circle fragment shader, red color, initially inactive). Call `initializeDeepgramClient()`.
- **resized()**: Split bottom button row — MIC ~28% width, gap, COOK ~70% width. Position recording indicator (small red circle near MIC button).
- **buttonClicked()**: Handle `mic_button_` click → `toggleRecording()`.
- **startRecording()**: Check DeepgramClient initialized. Connect WebSocket with transcript callback that calls `addMessage()` + `sidePanelMessageSubmitted()` on final transcripts (reusing existing chat flow). Start mic capture feeding audio to `DeepgramClient::sendAudioData()`. Update button text to "STOP", activate recording indicator.
- **stopRecording()**: Stop mic capture, disconnect WebSocket, reset button text to "MIC", deactivate indicator.
- **Interim results**: Optionally show partial transcript in `prompt_editor_` for visual feedback while speaking.

### 6. `src/common/load_save.h` / `load_save.cpp`
Add alongside existing `saveApiKeyPath()`/`getApiKeyPath()`:
```cpp
static void saveDeepgramApiKeyPath(const std::string& path);
static std::string getDeepgramApiKeyPath();
```
Implementation stores/reads `"deepgram_api_key_path"` in config JSON.

### 7. `src/interface/editor_components/synth_preset_selector.h`
Add to `MenuItems` enum: `kLoadDeepgramApiKey` (before `kNumMenuItems`).
Add method: `void loadDeepgramApiKeyFile();`

### 8. `src/interface/editor_components/synth_preset_selector.cpp`
- Add menu item: `options.addItem(kLoadDeepgramApiKey, "Load Deepgram API Key");` after the Claude key item.
- Add to `menuCallback()`: call `loadDeepgramApiKeyFile()`.
- Implement `loadDeepgramApiKeyFile()`: FileChooser → save path → re-initialize DeepgramClient.

### 9. `src/unity_build/common.cpp`
Add:
```cpp
#include "deepgram_client.cpp"
#include "microphone_capture.cpp"
```

### 10. `standalone/vital.jucer` (and `plugin/vital.jucer`)
- Add new source files (compile="0" for our .cpp/.h files).
- Add IXWebSocket third_party files (compile="1").
- Add header search path for ixwebsocket.
- Add `NSMicrophoneUsageDescription` to customPList.

---

## Implementation Order

1. **Vendor IXWebSocket** — download, place in `third_party/ixwebsocket/`, verify compilation
2. **LoadSave changes** — add Deepgram key path storage (small, isolated)
3. **Menu item** — add "Load Deepgram API Key" to preset selector menu
4. **DeepgramClient** — singleton with WebSocket connect/disconnect, audio send, JSON response parsing
5. **MicrophoneCapture** — audio device setup, downsampling, float-to-int16 conversion
6. **Unity build + jucer updates** — add includes, file entries, header paths, plist
7. **Side panel UI** — MIC button, recording indicator, wire up start/stop recording flow
8. **Polish** — error handling, graceful degradation when key not set, cleanup in destructor

## Verification
1. Build standalone app with no errors
2. Load Deepgram API key via menu
3. Click MIC button → verify microphone permission prompt appears (macOS)
4. Speak a phrase → verify partial transcript appears in text editor
5. Pause speaking → verify final transcript is sent as chat message through existing flow
6. Verify Claude API responds to the voice-transcribed message
7. Click MIC/STOP to end recording → verify clean shutdown
8. Test without Deepgram key configured → verify graceful error message
