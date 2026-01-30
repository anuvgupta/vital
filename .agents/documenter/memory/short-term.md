# Documenter Agent's Short-Term Memory

## Current Task: System Prompt Integration (2026-01-30)

Documented system prompt integration for Vital AI assistant:
- ClaudeApiClient loads SYSTEM_PROMPT.md from app bundle Resources (fallback to data dir)
- Sent via Anthropic API top-level "system" field
- build_macos.sh copies prompt file into app bundle post-build
- Files: src/common/claude_api_client.h, src/common/claude_api_client.cpp, build_macos.sh

## Note: File Path Inconsistency in steering.md

The Key Files Reference section has inconsistent file paths:
- Some use `vital/src/...` (incorrect - this path doesn't exist)
- Some use `src/...` (correct - files are at this path)

Files are located at `/Users/anuv/Documents/Code/Workspace/vital/workspace/vital/src/...`
The working directory is `/Users/anuv/Documents/Code/Workspace/vital/workspace/vital/`

I updated a few paths when touching those entries, but a full cleanup should be done in a future task.
