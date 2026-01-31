# Documenter Agent's Short-Term Memory

## Current Task: Markdown Rendering for Chat Messages (2026-01-30)

- Vendored md4c library in third_party/md4c/
- Created markdown_parser.h/cpp with SAX callback approach
- Updated side_panel to render markdown blocks (headings, code blocks, lists, quotes, etc.)
- Bug fix: bold font was using wrong font family (Montserrat vs Lato)

## Note: File Path Inconsistency in steering.md

The Key Files Reference section has inconsistent file paths:
- Some use `vital/src/...` (incorrect - this path doesn't exist)
- Some use `src/...` (correct - files are at this path)

A full cleanup should be done in a future task.
