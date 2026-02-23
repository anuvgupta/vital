# Documenter Agent's Short-Term Memory

## Status: Ready for next task

Last completed: Replace amplitude silence detection with Deepgram-activity inactivity timeout (2026-02-22)
- Replaced MicrophoneCapture amplitude-based silence detection with Timer-based Deepgram activity polling (250ms interval)
- TALK: 3s grace + 1.5s inactivity timeout + immediate stop on is_final
- VOICE CHAT: 5s grace + 15s inactivity timeout
- Fixed double "Thinking..." bug (voice callbacks + sidePanelMessageSubmitted both adding it)
- Fixed race condition: added recording_mode_ guard in TALK is_final callback
- Removed resetSilenceDetection() from MicrophoneCapture, removed talk_received_final_ flag
- Added Timer inheritance, timerCallback(), recording_start_ms_, last_deepgram_activity_ms_ to VitalSidePanel
- Files: side_panel.h, side_panel.cpp, microphone_capture.h, microphone_capture.cpp
