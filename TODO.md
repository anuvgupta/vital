# Vital Project TODO


## Features

### Open

- Autosave presets, checkpointing & restore chat at certain point
    - Prompt: we have this todo: `Autosave presets, checkpointing & restore chat at certain point` - this means, every time a user sends or receives a chat message, we save the current preset at time of sending or receiving. we can save into the main vital preset folder (research if this exists) under a subfolder called `autosaves`. and then, when a person hovers over a chat message sent or received, we chould see a restore button show up on the top right of that message's box, with a return or rounded arrow icon. clicking that button should open up a prompt asking if user wants to restore to this message. if user selects no/cancel, nothing happens. but if user selects yes/ok, then we should do three things: 1) reload the autosave preset from that save point, 2) remove the chat messages after that point from the ui, and 3) remove the chat messages after that point from the conversation history log in memory that will get sent on the next user message. do you have any questionst? do you think you can plan and implement this?
- Multimodal input to evaluate sound along with the preset for feedback. make it optional ie extended thinking /listening button OR you can just ask it to listen eventually
- Multi layer agentic flow with skills provided above - should execute on cloud to minimize network hops
    - architecture details
        - first, run just the latest user message through sonnet to have it decide which "skill" to call
        - then call the opus with the system prompt, selected skill prompt, preset schema, and if necessary also the vital handbook and sound design cookbook. add the conversation history with latest user message, and the current preset json.
        - DONT have a final summarization step - this would waste tokens and add latency - in future we could have it print out a natural language response as one of the preset json fields, and extract that. but for now a hardcoded "preset updated" is just fine.
    - first start with "knowledge base" and "preset generator" skills, then add "sound designer" as separate skill to see if it improves interpretation of nontechnical suond design descriptions
    - we need to research if there is already support for this in claude platform or openai platform. if not, we need to build our own latency-optimized orchestrater in AWS for example.


## Deprioritized
- Migrate to wispr flow for voice to text
- Mic calibration for silence vs talking (establish ambient noise level baseline) - do this when app starts (optional)
- VOICE CHAT mode: intelligent local VAD gating to avoid sending silence to Deepgram
    - Deepgram charges per-second of all audio sent, including silence. Always-on streaming is expensive.
    - Implement two-tier gating: (1) local energy/amplitude detection using existing `MicrophoneCapture` silence threshold (`kSilenceThreshold`) to gate whether audio is streamed to Deepgram; (2) Deepgram validates actual speech - if only noise/coughs with no valid transcripts, stop streaming and go back to local-only detection.
    - Flow: [always-on mic] -> local energy check -> above threshold? -> stream to Deepgram -> valid transcript? -> submit as message. Below threshold = free local listening only.
    - Future enhancement: wake word detection (e.g. "Hey Vital" via Picovoice Porcupine) as an additional gating layer for either ASK or TALK mode.

### Done
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

### Done
- Windows Voice Chat crash — null TLS socket due to Apple-only TLS define; fixed by integrating mbedTLS as Windows TLS backend + calling ix::initNetSystem()
- AI chat not working on Windows — system prompt and preset schema files not found due to macOS-only path resolution in ClaudeApiClient
- Limit output tokens to prevent wasting money
- Limit messages to a certain character limit
- Fix font sizes appearing different on different platforms
- Placeholder text in textarea doesn't wrap when window is shrunk (resized to be smaller) even though actual text in textarea does
- Integrate with deepgram for voice to text


