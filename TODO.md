# Vital Project TODO


## Features

### Open

- ...


### Long-Term

- Multimodal input to evaluate sound along with the preset for feedback. make it optional ie extended thinking /listening button OR you can just ask it to listen eventually
- Multiple thinking & output rounds (partially complete)
    - Router layer analyzes each message and decides: single-action (pass through) vs multi-action (split and execute sequentially)
    - Each sub-action sees updated preset state from previous steps
    - Future: Handle non-technical sound design descriptions (TBD -- currently returns sentinel "THIS REQUIRES COMPLEX SOUND DESIGN")
    


## Deprioritized
- Migrate to wispr flow for voice to text
- Mic calibration for silence vs talking (establish ambient noise level baseline) - do this when app starts (optional)
- VOICE CHAT mode: intelligent local VAD gating to avoid sending silence to Deepgram
    - Deepgram charges per-second of all audio sent, including silence. Always-on streaming is expensive.
    - Implement two-tier gating: (1) local energy/amplitude detection using existing `MicrophoneCapture` silence threshold (`kSilenceThreshold`) to gate whether audio is streamed to Deepgram; (2) Deepgram validates actual speech - if only noise/coughs with no valid transcripts, stop streaming and go back to local-only detection.
    - Flow: [always-on mic] -> local energy check -> above threshold? -> stream to Deepgram -> valid transcript? -> submit as message. Below threshold = free local listening only.
    - Future enhancement: wake word detection (e.g. "Hey Vital" via Picovoice Porcupine) as an additional gating layer for either ASK or TALK mode.

### Done
- Multi-layer agentic router flow — router uses tool_use to analyze message and decide single-action pass-through vs multi-action split/sequential execution
- Autosave presets, checkpointing & restore chat at certain point (hover restore button on user messages, archive on clear, orphan cleanup on startup, 50/20 caps)
- Edit mode for restore button (instant Claude-style, no confirmation dialog) — click to enter edit mode, edit and re-submit or ESC to cancel. Fully implemented with EditModeSnapshot state machine, cancel button, keyboard handler, and synth state rollback.
- Add a command shortcut (Cmd+K / Ctrl+K) to focus the chat prompt editor
- Chat clearing (clear/reset button in title row resets chat UI and API conversation history)
- Split mic into VOICE CHAT (always-on, 20s silence timeout, popup warning) and TALK (auto-stops on configurable silence) modes with SEND button
- Move away from Opus because its too expensive
- Support for mixed messages (containing markdown fences for code ie three backticks, alongside natural language descriptions)
- Markdown support in responses
- Rename chat panel title from "chat" to "sound designer"
- Voice-to-text input via Deepgram STT (MIC button, WebSocket streaming, real-time transcription)
- Turn off mic feature if no significant input sound for 2.5 seconds - make this configurable
- Rename mic button to talk button
- Queue messages when sent while agent is already thinking (request already in progress)
- Windows/Linux support for microphone permission handling (currently macOS only via mic_permission_mac.mm)



## Bugs

### Open
- Restore function is not working after first restore and replace

### Done
- Conversation history context pollution -- stale preset JSON and assistant JSON fences accumulating in history, wasting tokens
- Windows Voice Chat crash — null TLS socket due to Apple-only TLS define; fixed by integrating mbedTLS as Windows TLS backend + calling ix::initNetSystem()
- AI chat not working on Windows — system prompt and preset schema files not found due to macOS-only path resolution in ClaudeApiClient
- Limit output tokens to prevent wasting money
- Limit messages to a certain character limit
- Fix font sizes appearing different on different platforms
- Placeholder text in textarea doesn't wrap when window is shrunk (resized to be smaller) even though actual text in textarea does
- Integrate with deepgram for voice to text


