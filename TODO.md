# Vital Project TODO


## Features

### Open

- create new file for api requests on every new chat (rename th eold one if needed incrementally)

- Replace emptied SOUND_DESIGN_GUIDE.md (was 296KB SYNTHESIZER_COOKBOOK) with a compact, token-efficient sound design reference
    - Add examples of synth patches and corresponding descriptions by looking online at vital preset examples, adding and ai description of the sound (from multimodal) and the preset params in nat lang both --> find a way to automate this

### Long-Term

- Multimodal input to evaluate sound along with the preset for feedback. make it optional ie extended thinking /listening button OR you can just ask it to listen eventually

### Deprioritized
- Optimize router to also complete preset updates for single actions (see doc in .plans/prompts)
- Migrate to wispr flow for voice to text
- Mic calibration for silence vs talking (establish ambient noise level baseline) - do this when app starts (optional)
- VOICE CHAT mode: intelligent local VAD gating to avoid sending silence to Deepgram
    - Deepgram charges per-second of all audio sent, including silence. Always-on streaming is expensive.
    - Implement two-tier gating: (1) local energy/amplitude detection using existing `MicrophoneCapture` silence threshold (`kSilenceThreshold`) to gate whether audio is streamed to Deepgram; (2) Deepgram validates actual speech - if only noise/coughs with no valid transcripts, stop streaming and go back to local-only detection.
    - Flow: [always-on mic] -> local energy check -> above threshold? -> stream to Deepgram -> valid transcript? -> submit as message. Below threshold = free local listening only.
    - Future enhancement: wake word detection (e.g. "Hey Vital" via Picovoice Porcupine) as an additional gating layer for either ASK or TALK mode.

### Done
- Voice chat button refactoring — disappears on click, action button shows stop with indicator
- Cancel message functionality
- Multiple thinking & output rounds (partially complete)
    - Router layer analyzes each message and decides: single-action (pass through) vs multi-action (split and execute sequentially) vs sound design required (translate then re-route)
    - Each sub-action sees updated preset state from previous steps
- Reduce API token costs — research/analysis of request logs, history write-point audit, and implementation of 6 fixes (JSON leak, sub-action cleanup, reroute fix, router to Sonnet, cookbook rename, request logging)
- Multi-layer agentic router flow — router uses tool_use to analyze message and decide single-action pass-through vs multi-action split/sequential execution
- Autosave presets, checkpointing & restore chat at certain point (hover restore button on user messages, archive on clear, orphan cleanup on startup, 50/20 caps)
- Edit mode for restore button (instant Claude-style, no confirmation dialog) — click to enter edit mode, edit and re-submit or ESC to cancel. Fully implemented with EditModeSnapshot state machine, cancel button, keyboard handler, and synth state rollback.
- Sound design translation layer — router detects non-technical descriptions, translates via separate Claude call (SOUND_DESIGN_PROMPT.md + cookbook), re-routes through router for execution. Includes infinite loop guard, chat log debug output, and max_tokens fix.
- Add a command shortcut (Cmd+K / Ctrl+K) to focus the chat prompt editor
- Chat clearing (clear/reset button in title row resets chat UI and API conversation history)
- Split mic into VOICE CHAT (always-on, 15s silence timeout, popup warning) and talk mic icon overlay (auto-stops on configurable silence) modes with SEND button
- Move away from Opus because its too expensive
- Support for mixed messages (containing markdown fences for code ie three backticks, alongside natural language descriptions)
- Markdown support in responses
- Rename chat panel title from "chat" to "sound designer"
- Voice-to-text input via Deepgram STT (MIC button, WebSocket streaming, real-time transcription)
- Turn off mic feature if no significant input sound for 2.5 seconds - make this configurable
- Rename mic button to talk button
- Queue messages when sent while agent is already thinking (request already in progress)
- Windows/Linux support for microphone permission handling (currently macOS only via mic_permission_mac.mm)
- Re-architected side panel: inline action button (mic/send/stop 3-state), voice chat button inside textarea, removed button row
- Replaced "Ready to create!" intro message with centered logo + tagline intro screen (speech waveform icon + "Talk to your synthesizer")
- Preset save option from chatbot — router infers save intent, returns save_required + preset_name, saves to Sound Designer folder, shows confirmation in chat
- hide responses from sub-actions during sound design mult-actions but not for user direct multi-actions



## Bugs

### Open

### Done
- Cancel-edit button (X icon) cross-platform scaling bug — hardcoded pixel size caused mismatched icon/background on macOS vs Windows; fixed by scaling with `size_ratio_`
- Clear button, restore button, and repaint bugs after intro screen refactor — missing side effects from removed `addMessage()` call in `clearChat()`
- Silence detection values clarified and reworked — replaced amplitude-based silence detection with Deepgram-activity-based inactivity timeout (TALK: 3s grace + 1.5s timeout; VOICE CHAT: 5s grace + 15s timeout)
- Double "Thinking..." message in voice recording modes — voice callbacks were redundantly adding "Thinking..." alongside sidePanelMessageSubmitted(); removed from 3 callback sites
- Queued messages during multi-action leaving stranded step messages — `updateStatusMessage` now scans backwards for last kSystem/kStep (handles interleaved kUser), and `clearThinkingMessage()` called on queue so step lifecycle isn't disrupted
- Stale API responses arriving after clear conversation — `clearChat()` now bumps generation counter via `sidePanelClearRequested()` listener callback
- Stale API responses corrupting UI after edit-mode restore — added generation counter to invalidate in-flight async callbacks on restore/cancel
- Clear button is present when the chat is empty
- Restore function not working after first restore and cancel — checkpoint files deleted during restore, stale objects restored on cancel; fixed with `delete_files` param, `exitEditMode()` helper, and multiple secondary fixes
- Conversation history context pollution -- stale preset JSON and assistant JSON fences accumulating in history, wasting tokens
- Windows Voice Chat crash — null TLS socket due to Apple-only TLS define; fixed by integrating mbedTLS as Windows TLS backend + calling ix::initNetSystem()
- AI chat not working on Windows — system prompt and preset schema files not found due to macOS-only path resolution in ClaudeApiClient
- Limit output tokens to prevent wasting money
- Limit messages to a certain character limit
- Fix font sizes appearing different on different platforms
- Placeholder text in textarea doesn't wrap when window is shrunk (resized to be smaller) even though actual text in textarea does
- Integrate with deepgram for voice to text
- Sometimes prints out json data / examples - fixed?
- Conversation history not restoring on cancel-edit — `truncateHistoryTo()` is shrink-only; saved int size was useless after truncation. Fixed by storing full history snapshot in EditModeSnapshot
- "(preset updated)" showing up in chat window — changed placeholder to "Done.", plus restructured API calls to use XML-tagged sections separating history from current request

