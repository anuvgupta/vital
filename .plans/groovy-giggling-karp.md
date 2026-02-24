# Fix: clearChat() doesn't repaint after clearing

## Context
The clear button click handler calls `clearChat()` which clears `messages_` and calls `layoutMessages()`, but the UI never repaints. Previously, the `addMessage("Ready to create!", ...)` call at the end of `clearChat()` would trigger `repaintBackground()` via its internal scroll/layout logic. Since we removed that `addMessage` call, no repaint happens.

## File
`src/interface/editor_sections/side_panel.cpp`

## Fix
Add `repaintBackground();` at the end of `clearChat()`, after `layoutMessages();` (line ~1157).

## Verification
- Build, click clear → messages disappear, intro screen shows
