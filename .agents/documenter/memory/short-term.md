# Documenter Agent's Short-Term Memory

## Latest Task: Fix Windows AI Chat (2026-02-09)

- Fixed cross-platform bug: AI chat worked on macOS but not Windows
- Root cause: ClaudeApiClient resource file search paths didn't include exe-adjacent directory
- Added executable.getParentDirectory() as search path in loadSystemPrompt() and loadPresetSchema()
- File touched: src/common/claude_api_client.cpp
- Updated: CHANGELOG.md, TROUBLESHOOTING.md, TODO.md (moved to Bugs Done)
