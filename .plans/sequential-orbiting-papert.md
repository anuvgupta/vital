# Plan: Sound Design Translation Layer

## Context

The multi-layer agentic router currently handles two cases: pass-through (single action) and split-complex (multiple actions). A third case — non-technical sound descriptions like "blippy", "808 bass", "massive pad" — needs a translation step before the existing pipeline can handle them. The router already has a sentinel string `"THIS REQUIRES COMPLEX SOUND DESIGN"` but it's not handled.

The approach: when the router indicates sound design is needed, make a separate Claude call that translates the non-technical description into technical parameter adjustment instructions, then feed that back through the router for normal processing.

## Changes

### 1. Update router tool schema and response parsing (`claude_api_client.cpp` + `.h`)

**Router tool schema** — add `sound_design_required` boolean field alongside `actions`:
```json
{
  "actions": [],
  "sound_design_required": true
}
```

When `sound_design_required` is true, `actions` should be empty — no actions are needed since the original message is already available from the `routeAndExecute` parameter.

**Router system prompt** (`kRouterSystemPrompt`) — update the complex sound design rule:
- Instead of returning sentinel text in actions, set `sound_design_required: true` with empty actions `[]`
- For non-sound-design cases, set `sound_design_required: false` with actions as before
- Keep the other two paths unchanged

**RouterCallback** — update signature to include the flag:
```cpp
using RouterCallback = std::function<void(const StringArray& actions, bool sound_design_required, bool success, const String& error)>;
```

**Response parsing** in `routeMessageAsync` — extract `sound_design_required` from `input` alongside `actions`.

Update all existing callback invocations to pass `false` for `sound_design_required` on error/fallback paths.

### 2. Add sound design translation method (`claude_api_client.cpp` + `.h`)

**New method**:
```cpp
void sendSoundDesignTranslation(const String& message, ResponseCallback callback, const String& preset_json);
```
- Runs on background thread like existing methods
- Uses a separate system prompt: `sound_design_prompt_` (loaded from `SOUND_DESIGN_PROMPT.md` + `SYNTHESIZER_COOKBOOK.md`)
- Sends: conversation history + current preset (ephemeral) + user message
- Returns plain text (technical breakdown), NOT JSON
- Stores response in conversation history as assistant message

**Loading** — in `initialize()`, load `SOUND_DESIGN_PROMPT.md` and `SYNTHESIZER_COOKBOOK.md` from the same search paths as other prompt files. Concatenate them into `sound_design_prompt_`.

**New members**:
```cpp
String sound_design_prompt_;   // SOUND_DESIGN_PROMPT.md + cookbook
bool loadSoundDesignPrompt();
bool loadCookbook();
```

### 3. Create `SOUND_DESIGN_PROMPT.md` (new file alongside existing prompt files)

Path: `agents/vital-assistant/SOUND_DESIGN_PROMPT.md`

Content: System prompt instructing Claude to:
- Take a non-technical sound description and the current preset state
- Translate it into a concrete list of technical parameter adjustments in natural language
- Reference the cookbook for synthesis knowledge (waveforms, harmonics, modulation, effects)
- Output a numbered list of specific changes like "Set oscillator 1 to sawtooth wave, enable filter 1 low-pass at cutoff 60, add chorus at 50% wet..."
- Keep each item focused on 2-3 related parameter changes (so the router can pass them through or split them)
- Do NOT output JSON — output natural language instructions that the downstream preset-modification LLM can execute

### 4. Handle sound design path in `full_interface.cpp`

In `routeAndExecute`, add a new branch when `sound_design_required == true`:

```cpp
if (sound_design_required) {
    // Show status
    panel->updateStatusMessage("Designing sound...");

    // Get fresh preset JSON
    String preset_json = getPresetJson();

    // Call sound design translation
    ClaudeApiClient::instance().sendSoundDesignTranslation(message, [this, panel, message](
        const String& translation, bool success) {
        if (!success) {
            // Fallback: send original message directly
            sendApiRequest({message});
            return;
        }

        // Add original user message + translation to history
        // Then re-route the translation through the router
        routeAndExecute(translation);
    }, preset_json);
    return;
}
```

Key detail: the translation response is **shown in the chat UI** as an assistant message (so the user sees the technical breakdown), then fed back through `routeAndExecute`. The router will see the technical language and route it as pass-through or split-complex. This means the first two Claude calls (router + translation) produce a technical description, and the next calls (router again + preset modification) execute it.

**Guard against infinite loops**: Add a `bool is_sound_design_reroute_` flag. Set it `true` before the re-route call, check it at the top of `routeAndExecute` — if already in a reroute and router returns `sound_design_required` again, fall back to direct `sendApiRequest`.

### 5. Wire up conversation history correctly

- Original user message: added to history by `sendSoundDesignTranslation` (as "user")
- Translation response: added to history by `sendSoundDesignTranslation` (as "assistant")
- When re-routing the translation: the router sees the full history including the translation
- The downstream `sendApiRequest` will add the technical instruction as a new user message

## Files to modify
- `src/common/claude_api_client.h` — new callback signature, new methods, new members
- `src/common/claude_api_client.cpp` — router schema, response parsing, sound design translation method, loading
- `src/interface/editor_sections/full_interface.cpp` — sound design branch in `routeAndExecute`
- `src/interface/editor_sections/full_interface.h` — `is_sound_design_reroute_` flag

## New files
- `agents/vital-assistant/SOUND_DESIGN_PROMPT.md` — sound design translation system prompt

## Files to copy to build output (build scripts)
- `SOUND_DESIGN_PROMPT.md` and `SYNTHESIZER_COOKBOOK.md` need to be copied alongside `SYSTEM_PROMPT.md` and `PRESET_SCHEMA.md` in `build_windows.bat` / `build_macos.sh` / `build_linux.sh`

## Verification
1. Build on Windows: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
2. Test with non-technical input: "make it sound like a warm analog pad" — should see "Designing sound..." status, then technical breakdown, then preset changes applied
3. Test pass-through still works: "increase filter cutoff to 80" — should bypass sound design path
4. Test split-complex still works: "add wobble bass with distortion, reverb, and chorus" — should split into steps
5. Test fallback: if sound design translation fails, should fall back to direct sendApiRequest
