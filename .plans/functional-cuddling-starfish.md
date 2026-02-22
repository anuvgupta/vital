# Fix: Stale API responses arriving during edit-mode restore

## Context
When a user clicks "restore" on a conversation checkpoint while an API request is in flight, the async callback still fires and adds response messages to the now-truncated UI. This corrupts the restored state — the response appears where the old messages used to be.

The root cause: `sidePanelRestoreRequested()` sets `api_request_in_flight_ = false` and clears state, but the lambda callback captured by `sendApiRequest()` still holds valid pointers and runs normally when the HTTP response arrives.

## Approach: Generation counter

Add an `api_request_generation_` counter to `FullInterface`. Every async callback captures the generation at creation time. Every invalidation point (restore, cancel) bumps the generation. Callbacks silently discard responses when the generation doesn't match.

## Files to modify

### `src/interface/editor_sections/full_interface.h`
- Add `int api_request_generation_ = 0;` member next to `api_request_in_flight_`

### `src/interface/editor_sections/full_interface.cpp`

1. **`sendApiRequest()`** (~line 1238): Capture `int gen = api_request_generation_` before the lambda. Inside the callback, add an early return if `gen != api_request_generation_`.

2. **`routeAndExecute()`** (~line 1097): Same pattern for the router callback — capture generation, check at callback entry.

3. **`sidePanelRestoreRequested()`** (~line 1449): Add `++api_request_generation_;` alongside the existing `api_request_in_flight_ = false`.

4. **`clearChat()`** (called from side_panel): The existing flow already calls `archiveCheckpoints` then `clearConversation`, but if an API request is in flight, we should also bump the generation. This is handled because `clearChat` → `exitEditMode` flows through the side panel, but the full_interface `clearChat` equivalent should also bump. Check if `FullInterface` has its own clear handler — if not, the side panel's `clearChat` calls `ClaudeApiClient::clearConversation()` directly, so we need the generation bump in the restore path only.

## Verification
- Send a message, immediately click restore on an earlier checkpoint before the response arrives
- The stale response should be silently discarded
- Send a new message after restoring — it should work normally
- Cancel edit mode — original state should be fully restored
- Normal flow (no restore) should be unaffected
