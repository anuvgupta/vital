# Documenter Agent's Short-Term Memory

## Status: Ready for next task

Last completed: Replace SPEAK button with mic icon overlay (2026-02-22)
- Removed talk_button_ from side panel, added PlainShapeComponent mic icon on textarea
- Button row simplified: VOICE CHAT | SEND (was VOICE CHAT | TALK | SEND)
- Voice chat silence timeout reduced 20s -> 15s
- Key bugs: paintBackground covered by GL, mouse event forwarding, coordinate spaces, alpha blending, cursor
- Files: side_panel.h, side_panel.cpp, paths.h
