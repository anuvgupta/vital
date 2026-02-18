# Documenter Agent's Short-Term Memory

## Latest Task: Implement Claude-style edit mode for restore button (2026-02-17)

- Changed restore button from confirmation-dialog pattern to instant edit mode (Claude web UI)
- Clicking restore: removes user message + everything after, restores text to input box, shows X cancel button
- User can edit and re-submit, or press ESC / click X to undo edit and restore everything from snapshot
- `EditModeSnapshot` struct: stores full messages list, checkpoints, API history size, synth state
- Edit mode state machine: Normal → Edit (click restore) → Normal (submit or cancel)
- Files: side_panel.h/cpp, full_interface.h/cpp
- No bugs encountered; built successfully on first try

## Previous Task: Autosave Checkpoints & Chat Restore (2026-02-10)

- Implemented preset autosaving on every chat message send/receive
- Checkpoints saved to `<data_dir>/autosaves/checkpoint_<timestamp>.vital`
- Restore button (return arrow SVG) appears on hover over user messages
- Clicking restore: AlertWindow confirmation -> load preset, truncate chat UI + API history
- User message restore maps to next system message's checkpoint (post-AI-changes state)
- On CLEAR: archive checkpoints to named folder (first 7 words of first user message)
- On startup: orphaned checkpoints archived to `unsaved_session/`
- Caps: 50 checkpoints/session, 20 archived sessions
- Bug fix: MSVC `vector::resize()` needs default constructor; used `erase()` instead
- Files: side_panel.h/cpp, full_interface.h/cpp, claude_api_client.h/cpp, paths.h
- Updated: STEERING.md, CHANGELOG.md, TROUBLESHOOTING.md, TODO.md
