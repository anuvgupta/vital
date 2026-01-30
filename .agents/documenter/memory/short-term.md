# Documenter Agent's Short-Term Memory

## Current Task: Preset Schema Loading (2026-01-30)

Added PRESET_SCHEMA.md loading to ClaudeApiClient:
- `loadPresetSchema()` loads schema file from app bundle Resources (same pattern as system prompt)
- Schema appended to system_prompt_ in `initialize()`
- Build script updated to copy PRESET_SCHEMA.md into bundle
- Files: claude_api_client.h/cpp, build_macos.sh

## Note: File Path Inconsistency in steering.md

The Key Files Reference section has inconsistent file paths:
- Some use `vital/src/...` (incorrect - this path doesn't exist)
- Some use `src/...` (correct - files are at this path)

A full cleanup should be done in a future task.
