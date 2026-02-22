# Documenter Agent's Short-Term Memory

## Latest Task: Fix Multi-Action One-Shotting & Invalid Model ID (2026-02-21)

Post-testing bug fixes for token cost reduction work:

### Bug 1: Invalid Sonnet Model ID
- **Problem**: `kModelSonnet = "claude-sonnet-4-5-20241022"` doesn't exist (fabricated date)
- **When caught**: After switching router to Sonnet, API returned "Unknown model" 404
- **Root cause**: Constant created early, never validated, never used until router switch
- **Fix**: Updated to `claude-sonnet-4-5-20250929` in `src/common/claude_api_client.cpp`

### Bug 2: Multi-Action One-Shotting
- **Problem**: LLM saw full original message in history with first sub-action, completed everything at once
- **Symptoms**: Sub-actions 2+ returned "already done" text, wasting tokens
- **Root cause**: Line 1180 `addToHistory("user", message)` before sub-actions
- **Fix**: Removed line 1180, removed `cleanupSubActionHistory()` method, removed `pre_multi_action_history_size_` tracking member
- **Result**: Sub-actions stay in history as execution record; each runs independently

### Files Modified
- `src/common/claude_api_client.cpp`: Fixed model ID, removed cleanup method
- `src/common/claude_api_client.h`: Removed cleanup declaration
- `src/interface/editor_sections/full_interface.cpp`: Removed line 1180 call, removed cleanup calls and member resets
- `src/interface/editor_sections/full_interface.h`: Removed member declaration

### Key Learning
Model IDs must always be validated against official API docs. Never invent dates. When adding code paths that use old constants, revalidate them.
