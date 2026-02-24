# Plan: Fix conversation history not restoring on cancel-edit

## Context
When the user restores to a previous message (edit mode) and then cancels, the conversation history sent to the LLM is not properly restored. This causes downstream issues like the router having insufficient context (e.g., generating "Current Preset" instead of "808 Bass" when asked to save).

**Root cause:** `cancelEditMode()` calls `sidePanelCancelEditRequested(checkpoint, saved_api_history_size)` which calls `truncateHistoryTo(saved_api_history_size)`. But `truncateHistoryTo()` can only *shrink* — it does nothing when the target size is larger than the current size. During restore, history was already truncated to a smaller size, so the cancel can't grow it back.

**Flow demonstrating the bug:**
1. User sends 3 messages → history has 6 entries (3 user + 3 assistant)
2. User clicks restore on message 1 → `enterEditMode()` saves `saved_api_history_size = 6`
3. Restore truncates history to checkpoint's `api_history_size = 0` → history now empty
4. User cancels → `truncateHistoryTo(6)` called, but `6 < 0` is false → **no-op**, history stays empty
5. User sends "save this" → router sees empty history → "Current Preset"

## Fix

Replace the integer `saved_api_history_size` in `EditModeSnapshot` with a full copy of conversation history. On cancel, restore the full snapshot instead of calling `truncateHistoryTo()`.

### 1. Add snapshot/restore methods to ClaudeApiClient (`claude_api_client.h`, `claude_api_client.cpp`)

**NOTE:** I already partially made these changes before being asked to plan. Need to verify they're correct.

Add to public API in `claude_api_client.h`:
```cpp
struct HistoryEntry { String role; String content; };
std::vector<HistoryEntry> getHistorySnapshot() const;
void restoreHistory(const std::vector<HistoryEntry>& snapshot);
```

Implement in `claude_api_client.cpp` (after `truncateHistoryTo`):
- `getHistorySnapshot()`: copies `conversation_history_` into a vector of `HistoryEntry`
- `restoreHistory()`: clears `conversation_history_` and copies from the snapshot

### 2. Update EditModeSnapshot (`side_panel.h:67-73`)

Replace:
```cpp
int saved_api_history_size = 0;
```
With:
```cpp
std::vector<ClaudeApiClient::HistoryEntry> saved_api_history;
```

Need to `#include "claude_api_client.h"` in `side_panel.h` (or forward-declare).

### 3. Update enterEditMode (`side_panel.cpp:1420-1428`)

Replace:
```cpp
edit_snapshot_->saved_api_history_size = l->sidePanelGetApiHistorySize();
```
With:
```cpp
edit_snapshot_->saved_api_history = l->sidePanelGetApiHistorySnapshot();
```

### 4. Update cancelEditMode (`side_panel.cpp:1482-1485`)

Replace:
```cpp
l->sidePanelCancelEditRequested(edit_snapshot_->saved_synth_checkpoint,
                                 edit_snapshot_->saved_api_history_size);
```
With:
```cpp
l->sidePanelCancelEditRequested(edit_snapshot_->saved_synth_checkpoint,
                                 edit_snapshot_->saved_api_history);
```

### 5. Update Listener interface (`side_panel.h:94-96`)

Replace:
```cpp
virtual int sidePanelGetApiHistorySize() { return 0; }
virtual void sidePanelCancelEditRequested(const File& checkpoint, int api_history_size) {}
```
With:
```cpp
virtual std::vector<ClaudeApiClient::HistoryEntry> sidePanelGetApiHistorySnapshot() { return {}; }
virtual void sidePanelCancelEditRequested(const File& checkpoint, const std::vector<ClaudeApiClient::HistoryEntry>& history_snapshot) {}
```

Remove `sidePanelGetApiHistorySize()` since it's no longer needed.

### 6. Update FullInterface implementations (`full_interface.h`, `full_interface.cpp`)

**full_interface.h** — update declarations to match new Listener signatures:
```cpp
std::vector<ClaudeApiClient::HistoryEntry> sidePanelGetApiHistorySnapshot() override;
void sidePanelCancelEditRequested(const File& checkpoint, const std::vector<ClaudeApiClient::HistoryEntry>& history_snapshot) override;
```

Remove `sidePanelGetApiHistorySize()` and `int sidePanelGetApiHistorySize() override`.

**full_interface.cpp** — update implementations:
- `sidePanelGetApiHistorySnapshot()`: return `ClaudeApiClient::instance().getHistorySnapshot()`
- `sidePanelCancelEditRequested()`: call `ClaudeApiClient::instance().restoreHistory(history_snapshot)` instead of `truncateHistoryTo()`

### 7. Check: `sidePanelGetApiHistorySize` usage for checkpoints

The checkpoint system (`addCheckpoint`) still uses `int api_history_size` and `truncateHistoryTo()` for the *restore* direction (going back). This is correct — restore only ever truncates (makes smaller). The bug was only in the *cancel* direction (going forward to restore original state). So checkpoint code stays unchanged.

Verify that `sidePanelGetApiHistorySize()` is ONLY used in `enterEditMode()`. If it's used elsewhere for checkpoints, we need to keep it.

## Files to Modify
| File | What |
|------|------|
| `src/common/claude_api_client.h` | Add `HistoryEntry`, `getHistorySnapshot()`, `restoreHistory()` |
| `src/common/claude_api_client.cpp` | Implement snapshot/restore methods |
| `src/interface/editor_sections/side_panel.h` | Update `EditModeSnapshot`, `Listener` interface |
| `src/interface/editor_sections/side_panel.cpp` | Update `enterEditMode()`, `cancelEditMode()` |
| `src/interface/editor_sections/full_interface.h` | Update listener method overrides |
| `src/interface/editor_sections/full_interface.cpp` | Update implementations |

## Verification
1. Build with `build_windows.bat --skip-regenerate --no-run`
2. Test: Send 3+ messages building a sound, restore to message 1, cancel → send "save this" → should get a descriptive name (not "Current Preset")
3. Test: Restore 1 message back, cancel → verify history intact
4. Test: Restore 2+ messages back, cancel → verify history intact
5. Test: Restore and DON'T cancel (submit new message) → verify truncated history is correct for the new branch
