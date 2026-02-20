# Documenter Agent's Short-Term Memory

## Latest Task: Multi-Layer Agentic Chat Flow with Router (2026-02-19)

- Implemented router layer that analyzes user messages via Claude tool_use before sending to preset generation
- Router decides: single-action (pass through transparently) vs multi-action (split and execute sequentially)
- Multi-action flow: routeAndExecute() → router call → if >1 action, executeNextAction() chains them sequentially
- Each sub-action sees updated preset state; status messages transition ("Breaking it down..." → "Step 1/N..." → ...)
- Added to ClaudeApiClient: routeMessage() (tool_use router), addToHistory() (store messages without API call)
- Added to FullInterface: routeAndExecute(), executeNextAction() for orchestration
- Added to VitalSidePanel: updateStatusMessage() to replace last system message in-place
- Files modified: claude_api_client.h/cpp, full_interface.h/cpp, side_panel.h/cpp
- **Bugs fixed**:
  1. updateStatusMessage() wasn't visually updating → message.text updated but message.blocks not re-parsed; fixed by adding `message.blocks = parseMarkdown(text)`
  2. clearThinkingMessage() only matched "Thinking..." exactly → step status messages weren't cleaned up; fixed by pattern matching
  3. System message padding too large → split kPadding (14 for user) and kSystemPadding (4 for system)
  4. Router splitting too aggressively → tuned router prompt to batch simple changes and minimize splitting
- Complex sound design returns sentinel "THIS REQUIRES COMPLEX SOUND DESIGN" (TBD handling)
- Updated: STEERING.md, CHANGELOG.md, TODO.md, TROUBLESHOOTING.md

## Previous Task: Implement Claude-style edit mode for restore button (2026-02-17)

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
