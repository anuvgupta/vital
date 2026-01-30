# Documenter Agent's Short-Term Memory

## Current Task: JSON Diff-Based Preset Updates (2026-01-30)

Switched from full preset JSON responses to diff/merge patch approach:
- Claude returns only changed keys as JSON diff
- `mergeJson()` recursively merges diff into current preset
- Added `loadStateFromJson()` on SynthBase to apply merged result
- Increased kMaxTokens from 1024 to 4096
- Files: SYSTEM_PROMPT.md, full_interface.cpp/h, claude_api_client.cpp, synth_base.h

## Note: File Path Inconsistency in steering.md

The Key Files Reference section has inconsistent file paths:
- Some use `vital/src/...` (incorrect - this path doesn't exist)
- Some use `src/...` (correct - files are at this path)

A full cleanup should be done in a future task.
