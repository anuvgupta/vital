# Markdown Rendering for Chat Messages via md4c

## Overview
Add markdown rendering to AI chat messages using md4c (C markdown parser) integrated with the existing `AttributedString`/`TextLayout` rendering in `paintChatMessages()`.

## Supported Markdown Features
Bold, italic, inline code, fenced code blocks, headings, unordered/ordered lists, block quotes. No images/links/tables (not needed for chat).

## Files to Create
- `src/common/markdown_parser.h` — `MarkdownBlock`, `StyledRun` structs + parse function
- `src/common/markdown_parser.cpp` — md4c callback handler that produces `vector<MarkdownBlock>`
- `third_party/md4c/md4c.h` + `third_party/md4c/md4c.c` — vendored md4c library (2 files, MIT)

## Files to Modify
- `src/interface/editor_sections/side_panel.h` — `ChatMessage` stores parsed blocks instead of plain text
- `src/interface/editor_sections/side_panel.cpp` — Updated `calculateHeight()` and `paintChatMessages()` to render blocks
- `src/unity_build/common.cpp` — Add `#include "markdown_parser.cpp"`
- `vital.jucer` — Add md4c source files and include path

## Architecture

### Data Model
```
StyledRun { String text; bool bold, italic, code; }

MarkdownBlock {
    enum Type { kParagraph, kHeading, kCodeBlock, kListItem, kBlockQuote };
    Type type;
    int level;           // heading level (1-6) or list nesting depth
    bool ordered;        // for list items
    int list_index;      // for ordered lists
    String code_text;    // for code blocks (plain text, no runs)
    vector<StyledRun> runs;  // for everything else
}
```

### Parse Phase (markdown_parser.cpp)
- `vector<MarkdownBlock> parseMarkdown(const String& text)`
- md4c SAX callbacks accumulate blocks:
  - Track current font state (bold/italic/code stack) via `enter_span`/`leave_span`
  - On `text` callback, append `StyledRun` with current state to current block
  - On `enter_block`/`leave_block`, push/finalize `MarkdownBlock`s
  - Code blocks: collect all text into `code_text` field (single monospace block)

### Height Calculation
For each `MarkdownBlock`:
- **Paragraph/Heading/ListItem/BlockQuote**: Build `AttributedString` with per-run fonts, `createLayout()`, get height
- **Code block**: Monospace `AttributedString`, get height + extra padding for background
- **Heading**: Use `proportional_title()` with scaled size based on level
- **List item**: Add bullet/number width to left indent
- Sum all block heights + inter-block spacing

### Rendering
For each block in `paintChatMessages()`:
- **Paragraph**: Build multi-font `AttributedString` (bold→`withStyle(Font::bold)`, code→`monospace()`), draw via `TextLayout`
- **Code block**: `fillRoundedRectangle()` for dark background, then monospace `TextLayout`
- **Heading**: Larger `proportional_title()` font, `TextLayout`
- **List item**: Draw "•" or "1." at indent, then styled `TextLayout` at offset X
- **Block quote**: Draw 3px left border rect, then styled `TextLayout` at offset X
- **Inline code**: Use monospace font in `AttributedString` run (background highlight via manual rect drawing per-run is optional/future enhancement)

### ChatMessage Changes
```cpp
struct ChatMessage {
    String text;                          // keep raw text
    std::vector<MarkdownBlock> blocks;    // parsed blocks (populated on construction)
    Type type;
    // ... rest unchanged

    // Only system messages get markdown parsing; user messages render as plain text
};
```
- `addMessage()` calls `parseMarkdown()` for system messages
- `calculateHeight()` iterates blocks instead of single AttributedString
- User messages continue to render as plain text (no markdown parsing)

## Available Fonts
- `Fonts::instance()->proportional_regular()` — body text
- `Fonts::instance()->proportional_title()` — headings (bold/heavier weight)
- `Fonts::instance()->monospace()` — code blocks and inline code
- Bold: `font.withStyle(Font::bold)` on proportional_regular

## Build Integration
- Add `third_party/md4c/` to jucer include paths
- Add `md4c.c` to jucer as a compiled source (it's C, can't go in unity build)
- Add `markdown_parser.cpp` to `src/unity_build/common.cpp`

## Verification
- `./build_macos.sh --no-run` to verify compilation
- Run the app, send a message, verify Claude's markdown response renders with bold, code blocks, headings, lists
