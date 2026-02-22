/* Copyright 2013-2019 Matt Tytel
 *
 * vital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vital.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "JuceHeader.h"
#include <vector>

struct StyledRun {
    String text;
    bool bold = false;
    bool italic = false;
    bool code = false;
    bool strikethrough = false;
};

struct MarkdownBlock {
    enum Type {
        kParagraph,
        kHeading,
        kCodeBlock,
        kListItem,
        kBlockQuote,
        kHorizontalRule
    };

    Type type = kParagraph;
    int level = 0;              // heading level (1-6) or list nesting depth
    bool ordered = false;       // for list items
    int list_index = 0;         // for ordered list numbering
    String code_text;           // for code blocks (plain text, no styled runs)
    std::vector<StyledRun> runs;
};

std::vector<MarkdownBlock> parseMarkdown(const String& text);
