# Documenter Agent's Short-Term Memory

## Current Task: Preset JSON Injection (2026-01-30)

Added current preset JSON context to Claude API chat:
- When user sends a message, synth preset JSON is injected as a context message before the user's message
- Format: "This is the current preset JSON:\n```json\n{...}\n```"
- Base64 data (wave_data, samples/samples_stereo) is stripped before sending to save tokens
- Added public `SynthBase::getStateAsJson()` wrapper for protected `saveToJson()`
- Files: src/common/synth_base.h, src/common/claude_api_client.h/cpp, src/interface/editor_sections/full_interface.cpp

## Note: File Path Inconsistency in steering.md

The Key Files Reference section has inconsistent file paths:
- Some use `vital/src/...` (incorrect - this path doesn't exist)
- Some use `src/...` (correct - files are at this path)

Files are located at `/Users/anuv/Documents/Code/Workspace/vital/workspace/vital/src/...`
The working directory is `/Users/anuv/Documents/Code/Workspace/vital/workspace/vital/`

A full cleanup should be done in a future task.
