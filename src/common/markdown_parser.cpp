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

#include "markdown_parser.h"
#include "md4c.h"

namespace {

struct ParseContext {
    std::vector<MarkdownBlock> blocks;

    // Current block being built
    MarkdownBlock current_block;
    bool has_current_block = false;

    // Inline style state (can nest)
    int bold_depth = 0;
    int italic_depth = 0;
    int code_depth = 0;
    int strikethrough_depth = 0;

    // Block nesting
    bool in_code_block = false;
    int list_depth = 0;
    bool in_ordered_list = false;
    int ordered_list_start = 1;
    int list_item_index = 0;
    int blockquote_depth = 0;

    void startBlock(MarkdownBlock::Type type) {
        if (has_current_block)
            finishBlock();
        current_block = MarkdownBlock();
        current_block.type = type;
        has_current_block = true;
    }

    void finishBlock() {
        if (!has_current_block)
            return;
        // Only add non-empty blocks
        if (current_block.type == MarkdownBlock::kCodeBlock) {
            if (current_block.code_text.isNotEmpty())
                blocks.push_back(std::move(current_block));
        } else if (current_block.type == MarkdownBlock::kHorizontalRule) {
            blocks.push_back(std::move(current_block));
        } else if (!current_block.runs.empty()) {
            blocks.push_back(std::move(current_block));
        }
        current_block = MarkdownBlock();
        has_current_block = false;
    }

    void appendText(const String& text) {
        if (!has_current_block)
            return;

        if (in_code_block) {
            current_block.code_text += text;
            return;
        }

        StyledRun run;
        run.text = text;
        run.bold = bold_depth > 0;
        run.italic = italic_depth > 0;
        run.code = code_depth > 0;
        run.strikethrough = strikethrough_depth > 0;
        current_block.runs.push_back(std::move(run));
    }
};

int onEnterBlock(MD_BLOCKTYPE type, void* detail, void* userdata) {
    auto* ctx = static_cast<ParseContext*>(userdata);

    switch (type) {
        case MD_BLOCK_DOC:
            break;

        case MD_BLOCK_P:
            if (ctx->blockquote_depth > 0) {
                ctx->startBlock(MarkdownBlock::kBlockQuote);
                ctx->current_block.level = ctx->blockquote_depth;
            } else {
                ctx->startBlock(MarkdownBlock::kParagraph);
            }
            break;

        case MD_BLOCK_H: {
            auto* h = static_cast<MD_BLOCK_H_DETAIL*>(detail);
            ctx->startBlock(MarkdownBlock::kHeading);
            ctx->current_block.level = (int)h->level;
            break;
        }

        case MD_BLOCK_CODE: {
            ctx->startBlock(MarkdownBlock::kCodeBlock);
            ctx->in_code_block = true;
            break;
        }

        case MD_BLOCK_UL:
            ctx->list_depth++;
            ctx->in_ordered_list = false;
            break;

        case MD_BLOCK_OL: {
            auto* ol = static_cast<MD_BLOCK_OL_DETAIL*>(detail);
            ctx->list_depth++;
            ctx->in_ordered_list = true;
            ctx->ordered_list_start = (int)ol->start;
            ctx->list_item_index = (int)ol->start;
            break;
        }

        case MD_BLOCK_LI:
            ctx->startBlock(MarkdownBlock::kListItem);
            ctx->current_block.level = ctx->list_depth;
            ctx->current_block.ordered = ctx->in_ordered_list;
            if (ctx->in_ordered_list) {
                ctx->current_block.list_index = ctx->list_item_index;
                ctx->list_item_index++;
            }
            break;

        case MD_BLOCK_QUOTE:
            ctx->blockquote_depth++;
            break;

        case MD_BLOCK_HR:
            ctx->startBlock(MarkdownBlock::kHorizontalRule);
            ctx->finishBlock();
            break;

        default:
            break;
    }

    return 0;
}

int onLeaveBlock(MD_BLOCKTYPE type, void* detail, void* userdata) {
    (void)detail;
    auto* ctx = static_cast<ParseContext*>(userdata);

    switch (type) {
        case MD_BLOCK_P:
        case MD_BLOCK_H:
        case MD_BLOCK_LI:
            ctx->finishBlock();
            break;

        case MD_BLOCK_CODE:
            ctx->in_code_block = false;
            // Trim trailing newline from code blocks
            if (ctx->current_block.code_text.endsWithChar('\n'))
                ctx->current_block.code_text = ctx->current_block.code_text.dropLastCharacters(1);
            ctx->finishBlock();
            break;

        case MD_BLOCK_UL:
        case MD_BLOCK_OL:
            ctx->list_depth--;
            break;

        case MD_BLOCK_QUOTE:
            ctx->blockquote_depth--;
            break;

        default:
            break;
    }

    return 0;
}

int onEnterSpan(MD_SPANTYPE type, void* detail, void* userdata) {
    (void)detail;
    auto* ctx = static_cast<ParseContext*>(userdata);

    switch (type) {
        case MD_SPAN_STRONG: ctx->bold_depth++; break;
        case MD_SPAN_EM:     ctx->italic_depth++; break;
        case MD_SPAN_CODE:   ctx->code_depth++; break;
        case MD_SPAN_DEL:    ctx->strikethrough_depth++; break;
        default: break;
    }

    return 0;
}

int onLeaveSpan(MD_SPANTYPE type, void* detail, void* userdata) {
    (void)detail;
    auto* ctx = static_cast<ParseContext*>(userdata);

    switch (type) {
        case MD_SPAN_STRONG: ctx->bold_depth--; break;
        case MD_SPAN_EM:     ctx->italic_depth--; break;
        case MD_SPAN_CODE:   ctx->code_depth--; break;
        case MD_SPAN_DEL:    ctx->strikethrough_depth--; break;
        default: break;
    }

    return 0;
}

int onText(MD_TEXTTYPE type, const MD_CHAR* text, MD_SIZE size, void* userdata) {
    auto* ctx = static_cast<ParseContext*>(userdata);

    switch (type) {
        case MD_TEXT_NORMAL:
        case MD_TEXT_CODE:
            ctx->appendText(String::fromUTF8(text, (int)size));
            break;

        case MD_TEXT_SOFTBR:
            ctx->appendText(" ");
            break;

        case MD_TEXT_BR:
            ctx->appendText("\n");
            break;

        case MD_TEXT_ENTITY:
            // Simple entity handling
            {
                String entity = String::fromUTF8(text, (int)size);
                if (entity == "&amp;")       ctx->appendText("&");
                else if (entity == "&lt;")   ctx->appendText("<");
                else if (entity == "&gt;")   ctx->appendText(">");
                else if (entity == "&quot;") ctx->appendText("\"");
                else if (entity == "&nbsp;") ctx->appendText(" ");
                else ctx->appendText(entity);
            }
            break;

        default:
            ctx->appendText(String::fromUTF8(text, (int)size));
            break;
    }

    return 0;
}

} // anonymous namespace

std::vector<MarkdownBlock> parseMarkdown(const String& text) {
    ParseContext ctx;

    MD_PARSER parser;
    memset(&parser, 0, sizeof(parser));
    parser.abi_version = 0;
    parser.flags = MD_DIALECT_GITHUB;
    parser.enter_block = onEnterBlock;
    parser.leave_block = onLeaveBlock;
    parser.enter_span = onEnterSpan;
    parser.leave_span = onLeaveSpan;
    parser.text = onText;

    std::string utf8 = text.toStdString();
    md_parse(utf8.c_str(), (MD_SIZE)utf8.size(), &parser, &ctx);

    // Finish any remaining block
    ctx.finishBlock();

    return std::move(ctx.blocks);
}
