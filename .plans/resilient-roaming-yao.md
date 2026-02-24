# Fix Duplicate "Thinking..." Message in Talk Mode

## Context

In talk/speak mode (voice dictation), two "Thinking..." messages appear when a transcription is finalized. This is because the "Thinking..." message is added in **two places**:

1. **side_panel.cpp:730-733** — The TALK mode `is_final` callback clears 3 thinking messages then adds a new one
2. **full_interface.cpp:1080** — `sidePanelMessageSubmitted()` adds another one

A previous fix (commit `f3b9eb8`) was supposed to make `sidePanelMessageSubmitted()` the single source for "Thinking..." messages, but the code in the voice callback was not fully cleaned up — it still has 3x `clearThinkingMessage()` + `addMessage("Thinking...", ...)`.

## Fix

**File:** `src/interface/editor_sections/side_panel.cpp` (lines 730-733)

Remove the three `clearThinkingMessage()` calls and the `addMessage("Thinking...", ChatMessage::kSystem)` from the TALK mode `is_final` callback. The `sidePanelMessageSubmitted()` listener callback already handles adding the thinking message.

Before:
```cpp
        prompt_editor_->redoImage();
        clearThinkingMessage();
        clearThinkingMessage();
        clearThinkingMessage();
        addMessage("Thinking...", ChatMessage::kSystem);
        }
```

After:
```cpp
        prompt_editor_->redoImage();
        }
```

## Verification

- Build the project
- Use talk/speak mode to dictate a message
- Confirm only ONE "Thinking..." message appears after the user message
- Confirm the thinking message gets replaced by the AI response
- Test voice chat mode still works correctly (it doesn't have this issue)
