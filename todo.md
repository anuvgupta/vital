# Vital Agent TODO


## Features

### Open
- Add a command shortcut to activate the chat window. Use something familiar like command+esc
- Markdown support in responses
- Integrate with wispr flow for voice to text
- Autosave presets, checkpointing & restore chat at certain point
- Chat clearing
- Queue messages when sent while agent is already thinking (request already in progress)
- Multi layer agentic flow with skills provided above - should execute on cloud to minimize network hops
    - architecture details
        - first, run just the latest user message through sonnet to have it decide which "skill" to call
        - then call the opus with the system prompt, selected skill prompt, preset schema, and if necessary also the vital handbook and sound design cookbook. add the conversation history with latest user message, and the current preset json.
        - DONT have a final summarization step - this would waste tokens and add latency - in future we could have it print out a natural language response as one of the preset json fields, and extract that. but for now a hardcoded "preset updated" is just fine.
    - first start with "knowledge base" and "preset generator" skills, then add "sound designer" as separate skill to see if it improves interpretation of nontechnical suond design descriptions
    - we need to research if there is already support for this in claude platform or openai platform. if not, we need to build our own latency-optimized orchestrater in AWS for example.

### Done
- Move away from Opus because its too expensive
- Support for mixed messages (containing markdown fences for code ie three backticks, alongside natural language descriptions)


## Bugs

### Open
- Limit messages to a certain character & word limit
- Placeholder text in textarea doesn't wrap when window is shrunk (resized to be smaller) even though actual text in textarea does

### Done
- Limit output tokens to prevent wasting money
