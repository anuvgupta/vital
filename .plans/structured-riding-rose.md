# Plan: JSON Diff-Based Preset Updates

## Problem
Claude's `max_tokens` (1024) is too small for a full preset JSON (~4000+ lines). The response gets truncated, producing invalid JSON.

## Solution: Partial JSON Diff Approach

Instead of having Claude output the entire preset, have it output only a **JSON merge patch** — a small JSON object containing only the changed keys. We apply this on top of the current preset using a recursive merge.

### Format
Claude outputs a JSON object with only changed fields, using the same nested structure as the preset. Example:

```json
{
  "settings": {
    "filter_1_cutoff": 90.0,
    "osc_1_level": 0.7
  }
}
```

This gets recursively merged into the current preset JSON (like RFC 7396 JSON Merge Patch).

## Changes

### 1. Update `SYSTEM_PROMPT.md`
- Instruct Claude to output **only the changed parameters** as a partial JSON object matching the preset structure
- Explicitly say: do NOT output the full preset, only a diff/patch with changed keys
- Keep the `"settings"` wrapper so we can detect it's a preset update (existing detection: `parsed.count("settings")`)

### 2. Format preset JSON with indentation when injecting
**File:** `src/interface/editor_sections/full_interface.cpp` (~line 1028)
- Change `state.dump()` → `state.dump(2)` for readable multiline output so Claude can better parse parameter names

### 3. Add recursive JSON merge function
**File:** `src/interface/editor_sections/full_interface.cpp`
- Add a helper function `mergeJson(json& target, const json& patch)` that recursively merges patch keys into target
- For objects: recurse into matching keys, add new keys
- For non-objects (numbers, strings, arrays): replace the value

### 4. Change response handling to merge instead of replace
**File:** `src/interface/editor_sections/full_interface.cpp` (~lines 1043-1068)
- When we detect a JSON response with `"settings"`:
  1. Get current preset via `getStateAsJson()`
  2. Call `mergeJson(currentPreset, parsed)` to apply the diff
  3. Load the merged result via `loadStateFromJson(merged)`
  4. Show "Preset updated." in chat

### 5. Increase `max_tokens`
**File:** `src/common/claude_api_client.cpp`
- Increase `kMaxTokens` from 1024 to 4096 — even diffs might need room for wavetable line source data or multiple parameter changes

## Files to modify
- `agents/vital-assistant/SYSTEM_PROMPT.md` — diff output instructions
- `src/interface/editor_sections/full_interface.cpp` — pretty-print preset, merge logic, response handling
- `src/common/claude_api_client.cpp` — increase max_tokens

## Verification
- Build with `bash vital/build_macos.sh --no-run`
- Run the app, send a message like "increase the filter cutoff by 10%"
- Verify Claude returns a small JSON diff, not the full preset
- Verify the diff is merged and the synth UI updates
