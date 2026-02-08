# Documenter Agent's Short-Term Memory

## Latest Task: Chat Clear/Reset Button (2026-02-08)

- Added clear button (x icon) to side panel title row
- ClaudeApiClient gained `clearConversation()` public method
- UTF-8 rendering issue: raw hex bytes need `String(CharPointer_UTF8(...))` wrapper in JUCE
- Files touched: side_panel.h/cpp, claude_api_client.h/cpp
- Updated all docs: STEERING.md, CHANGELOG.md, TODO.md, TROUBLESHOOTING.md
