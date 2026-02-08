# Documenter Agent's Short-Term Memory

## Latest Task: Voice Button Rename & Layout (2026-02-08)

- Renamed ASK/TALK to VOICE CHAT/TALK with new layout: [VOICE CHAT (half)] [TALK (quarter)] [SEND (quarter)]
- VOICE CHAT has hardcoded 20s silence timeout via new `silence_timeout_override` param on MicrophoneCapture
- JUCE 6 AlertWindow API bug encountered and documented in TROUBLESHOOTING.md
- Updated STEERING.md core architecture, CHANGELOG.md, TODO.md, TROUBLESHOOTING.md
- Files touched: side_panel.h/cpp, microphone_capture.h/cpp, synth_preset_selector.cpp
