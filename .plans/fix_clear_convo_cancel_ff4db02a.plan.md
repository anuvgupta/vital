---
name: Fix clear convo cancel
overview: When the "clear conversation" button is pressed while an API response is in-flight, the response still arrives and gets displayed because `clearChat()` doesn't bump the `api_request_generation_` counter that the restore/cancel-edit handlers use to invalidate stale callbacks.
todos:
  - id: add-listener-method
    content: Add `sidePanelClearRequested()` virtual method to `VitalSidePanel::Listener` in side_panel.h
    status: completed
  - id: call-listener
    content: Call `sidePanelClearRequested()` on listeners from `VitalSidePanel::clearChat()` in side_panel.cpp
    status: completed
  - id: implement-override
    content: Declare and implement `sidePanelClearRequested()` override in FullInterface (h + cpp) to bump generation counter and reset in-flight state
    status: completed
isProject: false
---

# Fix: Clear Convo Not Cancelling In-Flight API Responses

## Root Cause

When "clear conversation" is clicked, `VitalSidePanel::clearChat()` ([side_panel.cpp](src/interface/editor_sections/side_panel.cpp) line 997) clears the UI and API history but never invalidates in-flight API requests. The restore and cancel-edit flows correctly bump `api_request_generation`_ in `FullInterface` (lines 1451 and 1490), which causes their callbacks to early-return when the generation doesn't match. `clearChat()` skips this step entirely.

## Fix

### 1. Add `sidePanelClearRequested()` to the Listener interface

In [side_panel.h](src/interface/editor_sections/side_panel.h) (line 95, inside the `Listener` class), add:

```cpp
virtual void sidePanelClearRequested() {}
```

### 2. Call listeners from `clearChat()`

In [side_panel.cpp](src/interface/editor_sections/side_panel.cpp), inside `clearChat()` (around line 1025, before or after clearing the API conversation history), add a listener callback:

```cpp
for (Listener* l : listeners_)
    l->sidePanelClearRequested();
```

### 3. Implement in `FullInterface`

In [full_interface.h](src/interface/editor_sections/full_interface.h), declare the override:

```cpp
void sidePanelClearRequested() override;
```

In [full_interface.cpp](src/interface/editor_sections/full_interface.cpp), implement it with the same invalidation pattern used by restore/cancel-edit:

```cpp
void FullInterface::sidePanelClearRequested() {
    ++api_request_generation_;
    api_request_in_flight_ = false;
    queued_messages_.clear();
    pending_actions_.clear();
    total_actions_ = 0;
    current_action_index_ = 0;
}
```

This is the same 6-line block already used at lines 1451-1456 and 1490-1495.

## Why This Works

All API callbacks (in `sendApiRequest`, `routeAndExecute`, and sound-design translation) capture `api_request_generation_` at call time and check it when the response arrives. Bumping the counter causes all in-flight callbacks to early-return and discard their responses, which is exactly the pattern already proven to work for restore and cancel-edit.