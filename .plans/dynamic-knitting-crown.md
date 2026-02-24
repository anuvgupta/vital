# Separate conversation history from current request in API calls

## Context
The router and main API both pass conversation history as flat alternating user/assistant messages in the Claude messages array. This causes the LLM (especially the router) to confuse old requests with the current one — e.g., re-including "turn on osc 3" from 5 messages ago as a sub-action of the current request. By structuring history as labeled context and the current request as a clearly separate block, the LLM can reliably distinguish what to act on.

## Files to modify
- `src/common/claude_api_client.cpp` — both `routeMessageAsync` and `sendMessagesAsync`
- `prompts/system_prompts/ROUTER_PROMPT.md` — update to reference the new format
- `prompts/system_prompts/SYSTEM_PROMPT.md` — update to reference the new format

## Changes

### 1. `routeMessageAsync` (claude_api_client.cpp ~line 573-588)

**Current:** Dumps `conversation_history_` as alternating messages, then appends current user message.

**New:** Build a single user message with two clearly labeled sections:

```
<conversation_history>
user: turn on osc 3
assistant: Done.
user: make it brighter
assistant: Increased filter cutoff.
</conversation_history>

<current_request>
make a warm pad
</current_request>
```

This is sent as ONE user message to the router. No alternating history messages at all.

### 2. `sendMessagesAsync` (claude_api_client.cpp ~line 405-437)

**Current:** Prior turns as alternating messages → preset JSON as injected user message → current turn messages.

**New:** Consolidate prior turns into a single context block, keep preset JSON injection, then current message:

- Message 1 (user): `<conversation_history>\nuser: ...\nassistant: ...\n</conversation_history>`
- Message 2 (assistant): `Understood, I have the conversation context.` (dummy to maintain alternation)
- Message 3 (user): Preset JSON context (existing)
- Message 4 (assistant): `Understood, I have the current preset state.` (dummy to maintain alternation) — actually this is already handled by the current approach since preset is injected as user message before the real user message
- Message 5 (user): The actual current request

Wait — actually the Claude API allows multiple user messages in a row by concatenating them. But to be safe with alternation, we can combine history + preset into one user message, then have the actual request as the next user message.

Simpler approach: Just two user messages:
- Message 1 (user): `<conversation_history>...</conversation_history>\n\n<current_preset_state>\n...\n</current_preset_state>`
- Message 2 (assistant): Short acknowledgment (to maintain alternation)
- Message 3 (user): The actual current request

Actually, even simpler — the Claude API concatenates consecutive same-role messages. So:
- Message 1 (user): History context block + preset JSON
- Message 2 (user): Current request
These get auto-merged, but the XML tags still make the boundary clear to the LLM.

**Simplest approach that works:** Keep it as one user message with clear XML-tagged sections. No need for alternation hacks.

### Revised approach

For **both** router and main API, instead of passing history as alternating messages, pass everything as a single user turn:

```xml
<conversation_history>
user: turn on osc 3
assistant: Done.
</conversation_history>

<current_preset>
{...json...}
</current_preset>

<current_request>
make a warm pad
</current_request>
```

For the **router**, drop the `<current_preset>` block (it doesn't need it).

For the **main API**, include all three sections.

This is one user message. System prompt stays in the system field.

### 3. Update prompts

**ROUTER_PROMPT.md:** Remove the line "ONLY route the LAST user message. Conversation history is provided for context only..." and instead say: "Your input has three sections: `<conversation_history>` (prior turns, for context only — already handled), `<current_request>` (the message to route). Only route the current request."

**SYSTEM_PROMPT.md:** Update the "Input" section to describe the new format: conversation history in `<conversation_history>`, current preset in `<current_preset>`, and the user's actual request in `<current_request>`.

### 4. History storage stays the same
The `conversation_history_` vector and `addMessage`/`addToHistory` logic stays unchanged — it's still used to build the text summary. We just format it differently when constructing the API request.

## Verification
1. Build: `build_windows.bat --skip-regenerate --no-run`
2. Test single action: "turn on osc 2" → should route as single action, apply correctly
3. Test multi-action: "turn on osc 2, set filter cutoff to 80, add chorus, set attack to 500ms" → should split into actions based on CURRENT request only, not include old requests
4. Test with history: send several requests in sequence, verify the router doesn't re-include old actions
5. Check `api_requests.log` to verify the new message format looks correct
