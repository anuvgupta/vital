# Fix: Checkpoint Files Deleted During Edit-Mode Restore

## Context

**Bug:** When a user clicks restore on a message, then cancels (or clears), and then tries to restore to the same or later message — it silently fails. Messages after the restore point remain visible in the UI, and the API conversation history is NOT truncated (stale context sent to LLM).

**Root cause:** `sidePanelRestoreRequested()` calls `removeCheckpointsAfter()` which **deletes checkpoint `.vital` files from disk**. But `enterEditMode()` saves a snapshot of the checkpoint vector *before* the restore. On cancel, the snapshot restores checkpoint objects into memory — but their files are gone. Subsequent restores find the checkpoint object via `getCheckpoint()` but `autosave_file.exists()` returns false → early return, no truncation, no API history cleanup.

**Impact:** CRITICAL — not only is the UI broken, but stale conversation history is sent to the LLM, causing incorrect/confusing responses.

## Changes

### 1. `removeCheckpointsAfter()` — add `delete_files` parameter
**File:** `src/interface/editor_sections/side_panel.h` (line 141) and `side_panel.cpp` (line 1060)

- Add `bool delete_files = true` parameter
- Only delete files from disk when `delete_files` is true
- Default true preserves existing behavior for any future callers

```cpp
// .h declaration
void removeCheckpointsAfter(int message_index, bool delete_files = true);

// .cpp implementation
void VitalSidePanel::removeCheckpointsAfter(int message_index, bool delete_files) {
  auto it = std::remove_if(checkpoints_.begin(), checkpoints_.end(),
      [message_index](const ChatCheckpoint& cp) {
        return cp.ui_message_index > message_index;
      });
  if (delete_files) {
    for (auto del = it; del != checkpoints_.end(); ++del)
      del->autosave_file.deleteFile();
  }
  checkpoints_.erase(it, checkpoints_.end());
}
```

### 2. `sidePanelRestoreRequested()` — pass `delete_files = false`
**File:** `src/interface/editor_sections/full_interface.cpp` (line 1385)

Since `sidePanelRestoreRequested` is only ever called from `enterEditMode` (edit-mode context), pass `false` to preserve files for cancel:

```cpp
panel->removeCheckpointsAfter(message_index - 1, false);  // Don't delete files — needed for cancel
```

### 3. `submitMessage()` — delete orphaned checkpoint files on edit commit
**File:** `src/interface/editor_sections/side_panel.cpp` (lines 855-861)

When the user submits (committing the edit), delete checkpoint files that were removed from the vector but kept on disk:

```cpp
if (edit_mode_) {
    // Delete orphaned checkpoint files from the tentative restore
    if (edit_snapshot_) {
      for (const auto& old_cp : edit_snapshot_->saved_checkpoints) {
        bool still_referenced = std::any_of(checkpoints_.begin(), checkpoints_.end(),
            [&](const ChatCheckpoint& cp) { return cp.autosave_file == old_cp.autosave_file; });
        if (!still_referenced && old_cp.autosave_file.exists())
          old_cp.autosave_file.deleteFile();
      }
    }
    edit_mode_ = false;
    edit_snapshot_.reset();
    if (cancel_edit_button_)
      cancel_edit_button_->setVisible(false);
}
```

### 4. `processRecordedSpeech()` — same orphan cleanup on voice submit
**File:** `src/interface/editor_sections/side_panel.cpp` (lines 827-832)

Apply the same orphan file cleanup as `submitMessage()`:

```cpp
if (edit_mode_) {
    if (edit_snapshot_) {
      for (const auto& old_cp : edit_snapshot_->saved_checkpoints) {
        bool still_referenced = std::any_of(checkpoints_.begin(), checkpoints_.end(),
            [&](const ChatCheckpoint& cp) { return cp.autosave_file == old_cp.autosave_file; });
        if (!still_referenced && old_cp.autosave_file.exists())
          old_cp.autosave_file.deleteFile();
      }
    }
    edit_mode_ = false;
    edit_snapshot_.reset();
    if (cancel_edit_button_)
      cancel_edit_button_->setVisible(false);
}
```

### 5. `clearChat()` — delete orphaned files before archiving
**File:** `src/interface/editor_sections/side_panel.cpp` (lines 984-990)

The existing edit_mode_ reset (from earlier fix) is already in place. Add orphan cleanup before `archiveCheckpoints()` so orphaned files don't get left behind:

```cpp
if (edit_mode_) {
    // Delete orphaned checkpoint files from the tentative restore
    if (edit_snapshot_) {
      for (const auto& old_cp : edit_snapshot_->saved_checkpoints) {
        bool still_referenced = std::any_of(checkpoints_.begin(), checkpoints_.end(),
            [&](const ChatCheckpoint& cp) { return cp.autosave_file == old_cp.autosave_file; });
        if (!still_referenced && old_cp.autosave_file.exists())
          old_cp.autosave_file.deleteFile();
      }
    }
    edit_mode_ = false;
    edit_snapshot_.reset();
    if (cancel_edit_button_)
      cancel_edit_button_->setVisible(false);
}
```

### 6. Extract helper to avoid code duplication
**File:** `src/interface/editor_sections/side_panel.h` and `side_panel.cpp`

Since the orphan-cleanup + edit-mode-exit logic is repeated in 3 places (submitMessage, processRecordedSpeech, clearChat), extract a private helper:

```cpp
// .h — private method
void exitEditMode();

// .cpp
void VitalSidePanel::exitEditMode() {
    if (!edit_mode_)
        return;

    // Delete orphaned checkpoint files from the tentative restore
    if (edit_snapshot_) {
        for (const auto& old_cp : edit_snapshot_->saved_checkpoints) {
            bool still_referenced = std::any_of(checkpoints_.begin(), checkpoints_.end(),
                [&](const ChatCheckpoint& cp) { return cp.autosave_file == old_cp.autosave_file; });
            if (!still_referenced && old_cp.autosave_file.exists())
                old_cp.autosave_file.deleteFile();
        }
    }

    edit_mode_ = false;
    edit_snapshot_.reset();
    if (cancel_edit_button_)
        cancel_edit_button_->setVisible(false);
}
```

Then replace all 3 call sites with `exitEditMode()`.

### 7. Add code comments explaining the invariant
Add clear comments at:
- `removeCheckpointsAfter` — explain why `delete_files` param exists
- `enterEditMode` — explain the snapshot/file lifecycle
- `sidePanelRestoreRequested` — explain why files are preserved

### 8. Documentation updates

**STEERING.md** — Add a section under architecture notes about the checkpoint lifecycle and the edit-mode invariant (snapshot preserves file references → files must not be deleted until edit is committed or cancelled).

**TROUBLESHOOTING.md** — Document the bug, root cause, and fix under a new entry.

## Files Modified

| File | Changes |
|------|---------|
| `src/interface/editor_sections/side_panel.h` | Add `delete_files` param to `removeCheckpointsAfter`, add private `exitEditMode()` |
| `src/interface/editor_sections/side_panel.cpp` | Implement `exitEditMode()`, update `removeCheckpointsAfter`, replace 3 inline edit-mode-exit blocks with `exitEditMode()` |
| `src/interface/editor_sections/full_interface.cpp` | Pass `false` to `removeCheckpointsAfter` in `sidePanelRestoreRequested` |
| `STEERING.md` | Document checkpoint lifecycle and edit-mode invariant |
| `TROUBLESHOOTING.md` | Document bug, root cause, and fix |

## Verification

1. **Build:** `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
2. **Test scenario (the original bug):**
   - Send 3+ messages, get responses for each
   - Click restore on message 1 → verify it truncates correctly
   - Click cancel (or clear)
   - Click restore on message 2 or 3 → verify it truncates correctly (was broken before)
   - Verify API responses are coherent (not referencing old conversation)
3. **Test cancel round-trip:**
   - Send messages, click restore, click cancel → all messages and checkpoints restored
   - Click restore on same message again → should work
4. **Test clear during edit mode:**
   - Click restore, then click clear → verify clean state, no stale cancel button
   - Send new messages, restore → should work
5. **Test voice input during edit mode:**
   - Click restore, use voice to submit → should commit edit correctly
