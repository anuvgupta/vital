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
#include "synth_section.h"
#include "open_gl_multi_quad.h"
#include "open_gl_image_component.h"
#include "claude_api_client.h"
#include "deepgram_client.h"
#include "microphone_capture.h"
#include "markdown_parser.h"

class OpenGlToggleButton;
class OpenGlTextEditor;
class Fonts;

struct ChatCheckpoint {
    int ui_message_index;
    int api_history_size;
    File autosave_file;
};

// Simple data structure for chat messages
struct ChatMessage
{
    enum Type
    {
        kUser,
        kSystem,
        kStep      // dimmer system message for step progress (e.g. "Step 1/3: ...")
    };

    String text;
    std::vector<MarkdownBlock> blocks;  // parsed markdown (system messages only)
    Type type;
    int y_position = 0;
    int height = 0;

    ChatMessage(const String &t, Type tp) : text(t), type(tp) {
        if (tp == kSystem || tp == kStep)
            blocks = parseMarkdown(t);
    }

    static int calculateHeight(const String &text, int width, float fontSize);
    static int calculateMarkdownHeight(const std::vector<MarkdownBlock>& blocks, int width, float fontSize);

    static constexpr int kPadding = 18;       // User message padding
    static constexpr int kSystemPadding = 6;   // System message padding
    static constexpr float kBaseFontSize = 15.0f;  // Multiplied by size_ratio_
    static constexpr float kCornerRadius = 8.0f;
};

struct EditModeSnapshot {
    std::vector<ChatMessage> saved_messages;
    std::vector<ChatCheckpoint> saved_checkpoints;
    int saved_api_history_size = 0;
    File saved_synth_checkpoint;
};

class VitalSidePanel : public SynthSection,
                       public TextEditor::Listener,
                       public ScrollBar::Listener,
                       public Timer
{
public:
    enum RecordingMode {
        kRecordingNone,
        kRecordingTalk,
        kRecordingVoiceChat
    };

    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void sidePanelButtonClicked() = 0;
        virtual void sidePanelMessageSubmitted(const String &message) {}
        virtual bool sidePanelRestoreRequested(int message_index) { return false; }
        virtual int sidePanelGetApiHistorySize() { return 0; }
        virtual File sidePanelSaveCheckpoint() { return File(); }
        virtual void sidePanelCancelEditRequested(const File& checkpoint, int api_history_size) {}
        virtual void sidePanelClearRequested() {}
    };

    VitalSidePanel();
    virtual ~VitalSidePanel();

    void paintBackground(Graphics &g) override;
    void paintBackgroundShadow(Graphics &g) override { paintTabShadow(g); }
    void resized() override;
    void buttonClicked(Button *clicked_button) override;

    // TextEditor::Listener
    void textEditorReturnKeyPressed(TextEditor &editor) override;
    void textEditorEscapeKeyPressed(TextEditor &editor) override;
    void textEditorTextChanged(TextEditor &editor) override;

    // ScrollBar::Listener
    void scrollBarMoved(ScrollBar *scrollBar, double newRangeStart) override;

    // Mouse events
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;
    void mouseMove(const MouseEvent& e) override;
    void mouseExit(const MouseEvent& e) override;
    void mouseUp(const MouseEvent& e) override;

    void addListener(Listener *listener) { listeners_.push_back(listener); }

    // API client
    void initializeApiClient();
    void initializeDeepgramClient();

    // Chat methods
    void submitMessage();
    void addMessage(const String &text, ChatMessage::Type type);
    void clearThinkingMessage();
    void removeStatusMessage(const String& text);
    void updateStatusMessage(const String& text, ChatMessage::Type newType = ChatMessage::kSystem);
    void addResponseMessage(const String &text);
    void clearChat();
    void focusPromptEditor();
    void saveChatLog();

    // Checkpoint methods
    int getMessageCount() const { return (int)messages_.size(); }
    ChatMessage::Type getMessageType(int index) const {
        if (index >= 0 && index < (int)messages_.size())
            return messages_[index].type;
        return ChatMessage::kSystem;
    }
    void addCheckpoint(int ui_message_index, int api_history_size, File autosave_file);
    void truncateMessagesTo(int count);
    void removeCheckpointsAfter(int message_index, bool delete_files = true);
    const ChatCheckpoint* getCheckpoint(int message_index) const;
    void archiveCheckpoints();
    void archiveLooseCheckpointsOnStartup();

    // Edit mode
    void enterEditMode(int message_index);
    void cancelEditMode();
    bool isInEditMode() const { return edit_mode_; }

    // Voice recording
    void startTalkRecording();
    void startVoiceChatRecording();
    void stopRecording();
    bool isRecording() const { return recording_mode_ != kRecordingNone; }
    RecordingMode recordingMode() const { return recording_mode_; }

    // Timer (Deepgram inactivity timeout)
    void timerCallback() override;

private:
    // Commits and exits edit mode: deletes orphaned checkpoint files that were
    // preserved during the tentative restore, then resets edit state. Called from
    // submitMessage(), processRecordedSpeech(), and clearChat().
    void exitEditMode();

    void layoutMessages();
    void scrollToBottom();
    void setScrollBarRange();
    void paintChatMessages(Graphics &g);
    void updateVoiceChatButtonColors();
    void updateCancelEditButtonColors();
    void updateActionButtonState();

    std::vector<Listener *> listeners_;
    std::unique_ptr<OpenGlTextEditor> prompt_editor_;
    std::unique_ptr<OpenGlToggleButton> action_button_;
    std::unique_ptr<OpenGlToggleButton> voice_chat_button_;
    std::unique_ptr<OpenGlToggleButton> clear_button_;
    std::unique_ptr<OpenGlQuad> clear_circle_bg_;
    std::unique_ptr<PlainShapeComponent> clear_x_icon_;
    Rectangle<int> clear_button_bounds_;
    bool clear_button_active_ = false;
    bool clear_button_hovered_ = false;

    // Chat state
    std::unique_ptr<OpenGlScrollBar> scroll_bar_;
    std::vector<ChatMessage> messages_;
    Rectangle<int> chat_bounds_;
    int total_content_height_ = 0;
    int scroll_position_ = 0;

    // Checkpoint state
    std::vector<ChatCheckpoint> checkpoints_;
    int hovered_message_index_ = -1;
    bool hovering_restore_button_ = false;
    Rectangle<int> restore_button_bounds_;

    // Edit mode state
    bool edit_mode_ = false;
    std::unique_ptr<EditModeSnapshot> edit_snapshot_;
    std::unique_ptr<OpenGlToggleButton> cancel_edit_button_;
    std::unique_ptr<PlainShapeComponent> cancel_edit_x_icon_;

    // Voice recording state
    std::unique_ptr<MicrophoneCapture> mic_capture_;
    std::unique_ptr<OpenGlQuad> voice_chat_recording_indicator_;
    enum ActionButtonMode { kActionMic, kActionSend, kActionStop };

    std::unique_ptr<PlainShapeComponent> mic_icon_shape_;
    std::unique_ptr<PlainShapeComponent> send_icon_shape_;
    std::unique_ptr<PlainShapeComponent> stop_icon_shape_;
    std::unique_ptr<OpenGlQuad> action_circle_bg_;
    std::unique_ptr<OpenGlQuad> mic_recording_indicator_;
    Rectangle<int> action_button_bounds_;
    bool action_button_hovered_ = false;
    ActionButtonMode action_button_mode_ = kActionMic;
    RecordingMode recording_mode_ = kRecordingNone;
    double recording_start_ms_ = 0.0;
    double last_deepgram_activity_ms_ = 0.0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VitalSidePanel)
};
