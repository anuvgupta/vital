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
#include "synth_constants.h"

class Paths {
  public:
    static constexpr int kLogoWidth = 1701;

    Paths() = delete;

    static Path fromSvgData(const void* data, size_t data_size) {
      std::unique_ptr<Drawable> drawable(Drawable::createFromImageData(data, data_size));
      return drawable->getOutlineAsPath();
    }

    static Path vitalRing() {
      Path path = fromSvgData((const void*)BinaryData::vital_ring_svg, BinaryData::vital_ring_svgSize);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(kLogoWidth, kLogoWidth, kLogoWidth, kLogoWidth), 0.2f);
      return path;
    }

    static Path vitalV() {
      Path path = fromSvgData((const void*)BinaryData::vital_v_svg, BinaryData::vital_ring_svgSize);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(kLogoWidth, kLogoWidth, kLogoWidth, kLogoWidth), 0.2f);
      return path;
    }

    static Path vitalWord() {
      return fromSvgData((const void*)BinaryData::vital_word_svg, BinaryData::vital_word_svgSize);
    }

    static Path vitalWordRing() {
      return fromSvgData((const void*)BinaryData::vital_word_ring_svg, BinaryData::vital_word_ring_svgSize);
    }

    static Path chorus() {
      return fromSvgData((const void*)BinaryData::chorus_svg, BinaryData::chorus_svgSize);
    }

    static Path compressor() {
      return fromSvgData((const void*)BinaryData::compressor_svg, BinaryData::compressor_svgSize);
    }

    static Path delay() {
      return fromSvgData((const void*)BinaryData::delay_svg, BinaryData::delay_svgSize);
    }

    static Path distortion() {
      return fromSvgData((const void*)BinaryData::distortion_svg, BinaryData::distortion_svgSize);
    }

    static Path equalizer() {
      return fromSvgData((const void*)BinaryData::equalizer_svg, BinaryData::equalizer_svgSize);
    }

    static Path effectsFilter() {
      return fromSvgData((const void*)BinaryData::effects_filter_svg, BinaryData::effects_filter_svgSize);
    }

    static Path flanger() {
      return fromSvgData((const void*)BinaryData::flanger_svg, BinaryData::flanger_svgSize);
    }

    static Path folder() {
      return fromSvgData((const void*)BinaryData::folder_svg, BinaryData::folder_svgSize);
    }

    static Path phaser() {
      return fromSvgData((const void*)BinaryData::phaser_svg, BinaryData::phaser_svgSize);
    }

    static Path reverb() {
      return fromSvgData((const void*)BinaryData::reverb_svg, BinaryData::reverb_svgSize);
    }

    static Path restoreIcon() {
      static const char svg[] =
        "<svg version=\"1.2\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 512 512\" width=\"512\" height=\"512\">"
        "<path fill-rule=\"evenodd\" fill=\"#ffffff\" d=\"m281.5 64.46c11.01 0.25 21.05 1.1 28.5 2.41 "
        "6.32 1.12 15.55 3.21 20.5 4.64 4.95 1.44 13.73 4.5 19.5 6.8 5.77 2.3 15.24 6.88 21.03 "
        "10.19 5.79 3.3 14.3 8.7 18.91 12 4.61 3.3 13.32 10.73 19.35 16.5 6.03 5.78 13.98 14.32 "
        "17.67 19 3.7 4.68 8.54 11.2 10.76 14.5 2.23 3.3 6.53 10.73 9.56 16.5 3.04 5.78 7.12 "
        "14.55 9.07 19.5 1.95 4.95 4.89 14.18 6.52 20.5 1.64 6.32 3.68 16.56 4.55 22.75 0.87 "
        "6.19 1.58 18 1.58 26.25 0 8.25-0.71 20.06-1.58 26.25-0.87 6.19-2.85 16.2-4.4 22.25"
        "-1.56 6.05-4.7 15.73-6.98 21.5-2.28 5.77-6.43 14.77-9.22 20-2.79 5.23-6.89 12.2-9.11 "
        "15.5-2.22 3.3-7.06 9.82-10.76 14.5-3.71 4.68-11.17 12.78-16.59 18.02-5.42 5.24-13.68 "
        "12.38-18.36 15.88-4.68 3.49-12.55 8.74-17.5 11.66-4.95 2.91-13.5 7.3-19 9.75-5.5 2.44"
        "-14.27 5.81-19.5 7.49-5.23 1.68-14 3.96-19.5 5.07-5.5 1.11-14.39 2.49-19.75 3.07-5.36 "
        "0.58-14.02 1.06-19.25 1.06-5.23 0-13.89-0.48-19.25-1.06-5.36-0.58-14.25-1.95-19.75-3.05"
        "-5.5-1.1-15.18-3.71-21.5-5.81-6.32-2.1-16.68-6.3-23-9.34-6.32-3.04-15.55-8.2-20.5-11.47"
        "-4.95-3.26-12.38-8.67-16.5-12.01-4.13-3.35-9.18-7.81-14.97-13.76l29.81-30 6.33 5.63c3.48 "
        "3.1 9.7 8.06 13.83 11.02 4.12 2.96 12 7.69 17.5 10.51 5.5 2.83 13.82 6.48 18.5 8.13 "
        "4.68 1.65 13.22 4.06 19 5.35 9.12 2.05 13.12 2.36 30.5 2.36 17.38 0 21.38-0.31 30.5"
        "-2.36 5.77-1.29 14.32-3.71 19-5.36 4.68-1.66 12.32-4.93 17-7.28 4.68-2.34 12.77-7.11 "
        "18-10.59 5.8-3.86 13.8-10.63 20.55-17.37 7.58-7.57 13.47-14.66 18.72-22.54 4.22-6.32 "
        "9.71-16.11 12.2-21.75 2.49-5.64 5.67-14.19 7.07-19 1.4-4.81 3.27-13.02 4.16-18.25 "
        "0.99-5.78 1.63-15.18 1.63-24 0-8.82-0.64-18.22-1.63-24-0.89-5.22-2.76-13.44-4.16-18.25"
        "-1.4-4.81-4.58-13.36-7.07-19-2.49-5.64-7.85-15.2-11.91-21.25-4.06-6.05-10.68-14.56"
        "-14.72-18.91-4.04-4.35-10.49-10.47-14.34-13.61-3.85-3.13-10.15-7.73-14-10.21-3.85-2.49"
        "-10.6-6.32-15-8.53-4.4-2.2-11.82-5.36-16.5-7.02-4.68-1.65-13.23-4.07-19-5.36-9.2-2.07"
        "-13.03-2.36-31-2.33-17.23 0.02-22.02 0.37-30 2.16-5.22 1.18-13.55 3.53-18.5 5.24-4.95 "
        "1.71-13.05 5.1-18 7.55-4.95 2.44-13.05 7.25-18 10.7-4.95 3.44-13 10.09-17.88 14.79"
        "-4.88 4.69-11.67 12.13-15.08 16.53-3.4 4.4-7.8 10.7-9.76 14-1.96 3.3-5.18 9.26-7.17 "
        "13.25-1.99 3.99-5.01 11.41-6.72 16.5-1.71 5.09-3.94 13.53-4.95 18.75-1.02 5.23-2.21 "
        "13.89-3.44 29.01l63.94-0.01-84.94 85-84.51-84.5 63.01-0.5 0.56-8.75c0.31-4.81 1.01"
        "-12.35 1.55-16.75 0.53-4.4 2.27-13.4 3.86-20 1.59-6.6 4.3-15.82 6.02-20.5 1.73-4.68 "
        "5.32-13 7.97-18.5 2.66-5.5 7.65-14.28 11.09-19.5 3.44-5.22 8.76-12.65 11.82-16.5 "
        "3.07-3.85 9.86-11.2 15.1-16.34 5.24-5.14 13.58-12.38 18.53-16.09 4.95-3.71 12.6-8.92 "
        "17-11.58 4.4-2.66 12.05-6.73 17-9.05 4.95-2.32 12.82-5.56 17.5-7.21 4.68-1.65 13.45"
        "-4.23 19.5-5.74 6.05-1.51 15.72-3.35 21.5-4.08 6.54-0.83 16.92-1.19 27.5-0.95zm-25.5 "
        "106.54h32l0.5 88.4 14 8.37c7.7 4.61 24.35 14.49 37 21.95 12.65 7.47 23.12 13.63 23.28 "
        "13.68 0.15 0.06-3.45 6.29-16.28 27.63l-4.5-2.69c-2.48-1.48-20.02-11.91-39-23.19-18.98"
        "-11.27-37.31-22.11-46.98-27.65z\"/>"
        "</svg>";
      return fromSvgData(svg, sizeof(svg) - 1);
    }

    static Path prev() {
      static const PathStrokeType arrow_stroke(0.1f, PathStrokeType::JointStyle::curved,
                                               PathStrokeType::EndCapStyle::rounded);

      Path prev_line, prev_shape;
      prev_line.startNewSubPath(0.65f, 0.3f);
      prev_line.lineTo(0.35f, 0.5f);
      prev_line.lineTo(0.65f, 0.7f);

      arrow_stroke.createStrokedPath(prev_shape, prev_line);
      prev_shape.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      prev_shape.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return prev_shape;
    }

    static Path next() {
      static const PathStrokeType arrow_stroke(0.1f, PathStrokeType::JointStyle::curved,
                                               PathStrokeType::EndCapStyle::rounded);

      Path next_line, next_shape;
      next_line.startNewSubPath(0.35f, 0.3f);
      next_line.lineTo(0.65f, 0.5f);
      next_line.lineTo(0.35f, 0.7f);

      arrow_stroke.createStrokedPath(next_shape, next_line);
      next_shape.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      next_shape.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return next_shape;
    }

    static Path clock() {
      static const float kClockAngle = 1.0f;
      static const float kClockWidth = 0.4f;
      static const float kBuffer = (1.0f - kClockWidth) / 2.0f;

      Path path;
      path.addPieSegment(kBuffer, kBuffer, kClockWidth, kClockWidth, 0.0f, kClockAngle - 2.0f * vital::kPi, 0.0f);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path dragDropArrows() {
      return fromSvgData((const void*)BinaryData::drag_drop_arrows_svg, BinaryData::drag_drop_arrows_svgSize);
    }

    static Path note() {
      static constexpr float kLeftAdjustment = 1.0f / 32.0f;
      static constexpr float kNoteWidth = 1.0f / 4.0f;
      static constexpr float kNoteHeight = 1.0f / 5.0f;
      static constexpr float kBarHeight = 2.0f / 5.0f;
      static constexpr float kBarWidth = 1.0f / 20.0f;
      static constexpr float kY = 1.0f - (1.0f - kBarHeight + kNoteHeight / 2.0f) / 2.0f;
      static constexpr float kX = (1.0f - kNoteWidth) / 2.0f - kLeftAdjustment;

      Path path;
      path.addEllipse(kX, kY - kNoteHeight / 2.0f, kNoteWidth, kNoteHeight);
      path.addRectangle(kX + kNoteWidth - kBarWidth, kY - kBarHeight, kBarWidth, kBarHeight);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path tripletNotes() {
      static constexpr float kNoteWidth = 1.0f / 5.0f;
      static constexpr float kNoteHeight = 1.0f / 6.0f;
      static constexpr float kX = (1.0f - 3.0f * kNoteWidth) / 2.0f;
      static constexpr float kBarWidth = 1.0f / 20.0f;
      static constexpr float kBarHeight = 1.0f / 4.0f;
      static constexpr float kY = 1.0f - (1.0f - kBarHeight) / 2.0f;

      Path path;
      path.addRectangle(kX + kNoteWidth - kBarWidth, kY - kBarHeight - kBarWidth,
                        2.0f * kNoteWidth + kBarWidth, kBarWidth);

      path.addEllipse(kX, kY - kNoteHeight / 2.0f, kNoteWidth, kNoteHeight);
      path.addRectangle(kX + kNoteWidth - kBarWidth, kY - kBarHeight, kBarWidth, kBarHeight);
      path.addEllipse(kX + kNoteWidth, kY - kNoteHeight / 2.0f, kNoteWidth, kNoteHeight);
      path.addRectangle(kX + kNoteWidth - kBarWidth + kNoteWidth, kY - kBarHeight, kBarWidth, kBarHeight);
      path.addEllipse(kX + 2.0f * kNoteWidth, kY - kNoteHeight / 2.0f, kNoteWidth, kNoteHeight);
      path.addRectangle(kX + kNoteWidth - kBarWidth + 2.0f * kNoteWidth, kY - kBarHeight, kBarWidth, kBarHeight);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path menu() {
      Path path;
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      path.addLineSegment(Line<float>(0.2f, 0.3f, 0.8f, 0.3f), 0.05f);
      path.addLineSegment(Line<float>(0.2f, 0.5f, 0.8f, 0.5f), 0.05f);
      path.addLineSegment(Line<float>(0.2f, 0.7f, 0.8f, 0.7f), 0.05f);
      return path;
    }

    static Path menu(int width) {
      static constexpr float kBuffer = 0.2f;
      static constexpr float kLineWidth = 0.04f;
      static constexpr float kSpacing = 0.2f;

      int buffer = std::round(width * kBuffer);
      int line_width = std::max<int>(1, width * kLineWidth);
      int spacing = width * kSpacing;

      float center = (line_width % 2) * 0.5f + (width / 2);
      Path path;
      path.addLineSegment(Line<float>(buffer, center - spacing, width - buffer, center - spacing), line_width);
      path.addLineSegment(Line<float>(buffer, center, width - buffer, center), line_width);
      path.addLineSegment(Line<float>(buffer, center + spacing, width - buffer, center + spacing), line_width);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(width, width, width, width), 0.2f);
      return path;
    }

    static Path plus(int width) {
      static constexpr float kBuffer = 0.35f;
      static constexpr float kLineWidth = 0.04f;

      int buffer = std::round(width * kBuffer);
      int line_width = std::max<int>(1, width * kLineWidth);

      float center = (line_width % 2) * 0.5f + (width / 2);
      Path path;
      path.addLineSegment(Line<float>(buffer, center, width - buffer, center), line_width);
      path.addLineSegment(Line<float>(center, buffer, center, width - buffer), line_width);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(width, width, width, width), 0.2f);
      return path;
    }

    static Path plusOutline() {
      static constexpr float kBuffer = 0.2f;
      static constexpr float kLineWidth = 0.15f;

      float start = kBuffer;
      float end = 1.0f - kBuffer;
      float close = 0.5f - kLineWidth * 0.5f;
      float far = 0.5f + kLineWidth * 0.5f;

      Path path;
      path.startNewSubPath(start, close);
      path.lineTo(start, far);
      path.lineTo(close, far);
      path.lineTo(close, end);
      path.lineTo(far, end);
      path.lineTo(far, far);
      path.lineTo(end, far);
      path.lineTo(end, close);
      path.lineTo(far, close);
      path.lineTo(far, start);
      path.lineTo(close, start);
      path.lineTo(close, close);
      path.lineTo(start, close);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path save(int width) {
      static constexpr float kLineWidth = 0.04f;
      static constexpr float kSpacingX = 0.3f;
      static constexpr float kSpacingY = 0.25f;
      static constexpr float kArrowMovement = 0.14f;
      static constexpr float kBoxWrap = 0.07f;

      int line_width = std::max<int>(1, width * kLineWidth);
      int spacing_x = width * kSpacingX;
      int spacing_y = width * kSpacingY;
      float movement = width * kArrowMovement / 2.0f;
      float wrap = width * kBoxWrap;

      float center = (line_width % 2) * 0.5f + (width / 2);

      Path outline;
      outline.startNewSubPath(center, center - spacing_y);
      outline.lineTo(center, center + movement);

      outline.startNewSubPath(center - 2 * movement, center - movement);
      outline.lineTo(center, center + movement);
      outline.lineTo(center + 2 * movement, center - movement);

      outline.startNewSubPath(center - spacing_x + wrap, center);
      outline.lineTo(center - spacing_x, center);
      outline.lineTo(center - spacing_x, center + spacing_y);
      outline.lineTo(center + spacing_x, center + spacing_y);
      outline.lineTo(center + spacing_x, center);
      outline.lineTo(center + spacing_x - wrap, center);

      Path path;
      PathStrokeType stroke(line_width, PathStrokeType::curved, PathStrokeType::rounded);
      stroke.createStrokedPath(path, outline);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(width, width, width, width), 0.2f);
      return path;
    }

    static Path downTriangle() {
      Path path;

      path.startNewSubPath(0.33f, 0.4f);
      path.lineTo(0.66f, 0.4f);
      path.lineTo(0.5f, 0.6f);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path upTriangle() {
      Path path;

      path.startNewSubPath(0.33f, 0.6f);
      path.lineTo(0.66f, 0.6f);
      path.lineTo(0.5f, 0.4f);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path exitX() {
      Path outline;
      outline.startNewSubPath(0.25f, 0.25f);
      outline.lineTo(0.75f, 0.75f);
      outline.startNewSubPath(0.25f, 0.75f);
      outline.lineTo(0.75f, 0.25f);

      Path path;
      PathStrokeType stroke(0.03f, PathStrokeType::curved, PathStrokeType::rounded);
      stroke.createStrokedPath(path, outline);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path thickX() {
      Path outline;
      outline.startNewSubPath(0.25f, 0.25f);
      outline.lineTo(0.75f, 0.75f);
      outline.startNewSubPath(0.25f, 0.75f);
      outline.lineTo(0.75f, 0.25f);

      Path path;
      PathStrokeType stroke(0.1f, PathStrokeType::curved, PathStrokeType::butt);
      stroke.createStrokedPath(path, outline);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path star() {
      Path path;
      path.addStar(Point<float>(0.5f, 0.5f), 5, 0.2f, 0.4f);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path keyboard() {
      Path path;
      path.addLineSegment(Line<float>(0.2f, 0.2f, 0.2f, 0.2f), 0.01f);
      path.addLineSegment(Line<float>(0.8f, 0.8f, 0.8f, 0.8f), 0.01f);

      path.startNewSubPath(0.24f, 0.35f);
      path.lineTo(0.24f, 0.65f);
      path.lineTo(0.41f, 0.65f);
      path.lineTo(0.41f, 0.5f);
      path.lineTo(0.35f, 0.5f);
      path.lineTo(0.35f, 0.35f);
      path.closeSubPath();

      path.startNewSubPath(0.48f, 0.65f);
      path.lineTo(0.48f, 0.35f);
      path.lineTo(0.52f, 0.35f);
      path.lineTo(0.52f, 0.5f);
      path.lineTo(0.58f, 0.5f);
      path.lineTo(0.58f, 0.65f);
      path.lineTo(0.42f, 0.65f);
      path.lineTo(0.42f, 0.5f);
      path.lineTo(0.48f, 0.5f);
      path.closeSubPath();

      path.startNewSubPath(0.65f, 0.35f);
      path.lineTo(0.76f, 0.35f);
      path.lineTo(0.76f, 0.65f);
      path.lineTo(0.59f, 0.65f);
      path.lineTo(0.59f, 0.5f);
      path.lineTo(0.65f, 0.5f);
      path.lineTo(0.65f, 0.35f);
      path.closeSubPath();

      return path;
    }

    static Path keyboardBordered() {
      Path board = keyboard();

      board.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.01f);
      board.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.01f);
      return board;
    }

    static Path fullKeyboard() {
      Path path;
      path.startNewSubPath(1, 0);
      path.lineTo(1, 2);
      path.lineTo(23, 2);
      path.lineTo(23, 1);
      path.lineTo(15, 1);
      path.lineTo(15, 0);
      path.closeSubPath();

      path.startNewSubPath(29, 0);
      path.lineTo(29, 1);
      path.lineTo(25, 1);
      path.lineTo(25, 2);
      path.lineTo(47, 2);
      path.lineTo(47, 1);
      path.lineTo(43, 1);
      path.lineTo(43, 0);
      path.closeSubPath();

      path.startNewSubPath(57, 0);
      path.lineTo(57, 1);
      path.lineTo(49, 1);
      path.lineTo(49, 2);
      path.lineTo(71, 2);
      path.lineTo(71, 0);
      path.closeSubPath();

      path.startNewSubPath(73, 0);
      path.lineTo(73, 2);
      path.lineTo(95, 2);
      path.lineTo(95, 1);
      path.lineTo(83, 1);
      path.lineTo(83, 0);
      path.closeSubPath();

      path.startNewSubPath(99, 0);
      path.lineTo(99, 1);
      path.lineTo(97, 1);
      path.lineTo(97, 2);
      path.lineTo(119, 2);
      path.lineTo(119, 1);
      path.lineTo(112, 1);
      path.lineTo(112, 0);
      path.closeSubPath();

      path.startNewSubPath(128, 0);
      path.lineTo(128, 1);
      path.lineTo(121, 1);
      path.lineTo(121, 2);
      path.lineTo(143, 2);
      path.lineTo(143, 1);
      path.lineTo(141, 1);
      path.lineTo(141, 0);
      path.closeSubPath();

      path.startNewSubPath(157, 0);
      path.lineTo(157, 1);
      path.lineTo(145, 1);
      path.lineTo(145, 2);
      path.lineTo(167, 2);
      path.lineTo(167, 0);
      path.closeSubPath();

      return path;
    }

    static Path gear() {
      static constexpr float kRadius = 0.3f;
      static constexpr float kGearOuterRatio = 1.2f;
      static constexpr int kNumGearTeeth = 8;

      Path path;
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      float offset = 0.5f - kRadius;
      float diameter = 2.0f * kRadius;
      path.addPieSegment(offset, offset, diameter, diameter, 0.0f, 2.0f * vital::kPi, 0.5f);
      for (int i = 0; i < kNumGearTeeth; ++i) {
        float phase = 2.0f * i * vital::kPi / kNumGearTeeth;
        float x_offset = kRadius * cosf(phase);
        float y_offset = kRadius * sinf(phase);
        Line<float> line(0.5f + x_offset, 0.5f + y_offset,
                         0.5f + kGearOuterRatio * x_offset, 0.5f + kGearOuterRatio * y_offset);
        path.addLineSegment(line, 0.13f);
      }

      return path;
    }

    static Path magnifyingGlass() {
      static constexpr float kRadius = 0.22f;
      static constexpr float kWidthRatio = 0.3f;
      static constexpr float kGlassOffset = 0.2f;
      static constexpr float kSqrt2 = 1.41421356237f;

      Path path;
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      float diameter = 2.0f * kRadius;
      path.addPieSegment(kGlassOffset, kGlassOffset, diameter, diameter, 0.0f, 2.0f * vital::kPi, 1.0f - kWidthRatio);

      float line_width = kWidthRatio * kRadius;
      float line_start = kGlassOffset + kSqrt2 * kRadius + line_width / 2.0f;
      path.addLineSegment(Line<float>(line_start, line_start, 1.0f - kGlassOffset, 1.0f - kGlassOffset), line_width);

      return path;
    }

    static Path save() {
      Path outline;
      outline.startNewSubPath(0.5f, 0.25f);
      outline.lineTo(0.5f, 0.6f);
      outline.startNewSubPath(0.35f, 0.45f);
      outline.lineTo(0.5f, 0.6f);
      outline.lineTo(0.65f, 0.45f);

      outline.startNewSubPath(0.25f, 0.5f);
      outline.lineTo(0.2f, 0.5f);
      outline.lineTo(0.2f, 0.75f);
      outline.lineTo(0.8f, 0.75f);
      outline.lineTo(0.8f, 0.5f);
      outline.lineTo(0.75f, 0.5f);

      Path path;
      PathStrokeType stroke(0.05f, PathStrokeType::curved, PathStrokeType::rounded);
      stroke.createStrokedPath(path, outline);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path loop() {
      Path outline;
      outline.startNewSubPath(0.68f, 0.3f);
      outline.lineTo(0.85f, 0.3f);
      outline.lineTo(0.85f, 0.7f);
      outline.lineTo(0.15f, 0.7f);
      outline.lineTo(0.15f, 0.3f);
      outline.lineTo(0.61f, 0.3f);
      PathStrokeType outer_stroke(0.12f, PathStrokeType::curved, PathStrokeType::rounded);

      Path path;
      outer_stroke.createStrokeWithArrowheads(path, outline, 0.0f, 0.0f, 0.4f, 0.26f);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path bounce() {
      Path left_outline, right_outline;
      left_outline.startNewSubPath(0.5f, 0.5f);
      left_outline.lineTo(0.0f, 0.5f);
      left_outline.startNewSubPath(0.5f, 0.5f);
      left_outline.lineTo(1.0f, 0.5f);

      PathStrokeType stroke(0.12f, PathStrokeType::curved, PathStrokeType::butt);
      Path left_path, right_path;
      stroke.createStrokeWithArrowheads(left_path, left_outline, 0.0f, 0.0f, 0.4f, 0.26f);
      stroke.createStrokeWithArrowheads(right_path, right_outline, 0.0f, 0.0f, 0.4f, 0.26f);

      Path path;
      path.addPath(left_path);
      path.addPath(right_path);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path bipolar() {
      Path left_outline, right_outline;
      left_outline.startNewSubPath(0.3f, 0.5f);
      left_outline.lineTo(0.0f, 0.5f);
      left_outline.startNewSubPath(0.7f, 0.5f);
      left_outline.lineTo(1.0f, 0.5f);

      PathStrokeType stroke(0.12f, PathStrokeType::curved, PathStrokeType::rounded);
      Path left_path, right_path;
      stroke.createStrokeWithArrowheads(left_path, left_outline, 0.0f, 0.0f, 0.4f, 0.26f);
      stroke.createStrokeWithArrowheads(right_path, right_outline, 0.0f, 0.0f, 0.4f, 0.26f);

      Path path;
      path.addEllipse(0.4f, 0.4f, 0.2f, 0.2f);
      path.addPath(left_path);
      path.addPath(right_path);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path shuffle() {
      Path over;
      over.startNewSubPath(0.1f, 0.7f);
      over.lineTo(0.25f, 0.7f);
      over.lineTo(0.55f, 0.3f);
      over.lineTo(0.95f, 0.3f);

      Path under_first;
      under_first.startNewSubPath(0.1f, 0.3f);
      under_first.lineTo(0.25f, 0.3f);
      under_first.lineTo(0.325f, 0.4f);

      Path under_second;
      under_second.startNewSubPath(0.475f, 0.6f);
      under_second.lineTo(0.55f, 0.7f);
      under_second.lineTo(0.95f, 0.7f);

      PathStrokeType stroke(0.12f, PathStrokeType::curved, PathStrokeType::butt);
      Path over_path;
      stroke.createStrokeWithArrowheads(over_path, over, 0.0f, 0.0f, 0.35f, 0.26f);
      Path under_path_first;
      stroke.createStrokedPath(under_path_first, under_first);
      Path under_path_second;
      stroke.createStrokeWithArrowheads(under_path_second, under_second, 0.0f, 0.0f, 0.35f, 0.26f);

      Path path;
      path.addPath(over_path);
      path.addPath(under_path_first);
      path.addPath(under_path_second);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path pencil() {
      static constexpr float kPencilDimension = 0.14f;
      static constexpr float kEraserLength = 0.6f * kPencilDimension;
      static constexpr float kSeparatorWidth = 0.15f * kPencilDimension;
      static constexpr float kPencilRemoval = kEraserLength + kSeparatorWidth;
      static constexpr float kBorder = 0.22f;

      Path path;
      path.startNewSubPath(kBorder, 1.0f - kBorder);
      path.lineTo(kBorder + kPencilDimension, 1.0f - kBorder);
      path.lineTo(1.0f - kBorder - kPencilRemoval, kBorder + kPencilDimension + kPencilRemoval);
      path.lineTo(1.0f - kBorder - kPencilRemoval - kPencilDimension, kBorder + kPencilRemoval);
      path.lineTo(kBorder, 1.0f - kBorder - kPencilDimension);
      path.closeSubPath();

      path.startNewSubPath(1.0f - kBorder - kPencilDimension, kBorder);
      path.lineTo(1.0f - kBorder, kBorder + kPencilDimension);
      path.lineTo(1.0f - kBorder - kEraserLength, kBorder + kPencilDimension + kEraserLength);
      path.lineTo(1.0f - kBorder - kEraserLength - kPencilDimension, kBorder + kEraserLength);
      path.closeSubPath();
      
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path halfSinCurve() {
      static constexpr float kBorder = 0.15f;
      static constexpr float kLineWidth = 0.1f;
      static constexpr float kEndpointStrokeWidth = 0.08f;
      static constexpr float kEndpointRadius = 0.09f;
      static constexpr int kNumCurvePoints = 16;
      static constexpr float kFullRadians = vital::kPi * 2.0f;
      static constexpr float kBumpIn = kEndpointRadius;
      static constexpr float kAdjustXIn = kBumpIn + kEndpointRadius / 2.0f;

      Path curve;
      float start_x = kBorder + kAdjustXIn;
      float start_y = 1.0f - kBorder - kBumpIn;
      float end_x = 1.0f - kBorder - kAdjustXIn;
      float end_y = kBorder + kBumpIn;

      curve.startNewSubPath(start_x, end_x);
      for (int i = 0; i < kNumCurvePoints; ++i) {
        float t = (1.0f + i) / kNumCurvePoints;
        float x = t * end_x + (1.0f - t) * start_x;
        float y_t = sinf((t - 0.5f) * vital::kPi) * 0.5f + 0.5f;
        float y = y_t * end_y + (1.0f - y_t) * start_y;
        curve.lineTo(x, y);
      }

      Path path;
      PathStrokeType line_stroke(kLineWidth, PathStrokeType::curved, PathStrokeType::butt);
      PathStrokeType endpoint_stroke(kEndpointStrokeWidth, PathStrokeType::curved, PathStrokeType::butt);
      line_stroke.createStrokedPath(path, curve);

      Path arc;
      arc.addCentredArc(end_x + kBumpIn, end_y, kEndpointRadius, kEndpointRadius, 0.0f, 0.0f, kFullRadians, true);
      arc.addCentredArc(start_x - kBumpIn, start_y, kEndpointRadius, kEndpointRadius, 0.0f, 0.0f, kFullRadians, true);
      Path end_points;
      endpoint_stroke.createStrokedPath(end_points, arc);
      path.addPath(end_points);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path ellipses() {
      Path path;
      path.addEllipse(0.1f, 0.4f, 0.2f, 0.2f);
      path.addEllipse(0.4f, 0.4f, 0.2f, 0.2f);
      path.addEllipse(0.7f, 0.4f, 0.2f, 0.2f);

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path paintBrush() {
      static constexpr float kBrushWideDimension = 0.3f;
      static constexpr float kBrushHandleDimension = 0.08f;
      static constexpr float kBrushLength = 0.6f * kBrushWideDimension;
      static constexpr float kSeparatorWidth = 0.15f * kBrushWideDimension;
      static constexpr float kConnectionDistance = kBrushLength + kSeparatorWidth;
      static constexpr float kHandleDistance = kConnectionDistance + kBrushWideDimension * 0.8f;
      static constexpr float kBorder = 0.15f;

      Path path;
      path.startNewSubPath(kBorder, 1.0f - kBorder);
      path.lineTo(kBorder + kBrushHandleDimension, 1.0f - kBorder);
      path.lineTo(1.0f - kBorder - kHandleDistance, kBorder + kBrushHandleDimension + kHandleDistance);
      path.lineTo(1.0f - kBorder - kConnectionDistance, kBorder + kBrushWideDimension + kConnectionDistance);
      path.lineTo(1.0f - kBorder - kConnectionDistance - kBrushWideDimension, kBorder + kConnectionDistance);
      path.lineTo(1.0f - kBorder - kHandleDistance - kBrushHandleDimension, kBorder + kHandleDistance);
      path.lineTo(kBorder, 1.0f - kBorder - kBrushHandleDimension);
      path.closeSubPath();

      path.startNewSubPath(1.0f - kBorder - kBrushWideDimension, kBorder);
      path.lineTo(1.0f - kBorder, kBorder + kBrushWideDimension);
      path.lineTo(1.0f - kBorder - kBrushLength, kBorder + kBrushWideDimension + kBrushLength);
      path.lineTo(1.0f - kBorder - kBrushLength - kBrushWideDimension, kBorder + kBrushLength);
      path.closeSubPath();

      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path createFilterStroke(const Path& outline, float line_thickness = 0.1f) {
      PathStrokeType stroke(line_thickness, PathStrokeType::curved, PathStrokeType::rounded);

      Path path;
      stroke.createStrokedPath(path, outline);
      return path;
    }

    static Path lowPass(float line_thickness = 0.1f) {
      Path outline;
      outline.startNewSubPath(1.0f, 0.8f);
      outline.lineTo(0.7f, 0.3f);
      outline.lineTo(0.5f, 0.5f);
      outline.lineTo(0.0f, 0.5f);
      Path path = createFilterStroke(outline, line_thickness);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.2f);
      return path;
    }

    static Path highPass() {
      Path outline;
      outline.startNewSubPath(0.0f, 0.8f);
      outline.lineTo(0.3f, 0.3f);
      outline.lineTo(0.5f, 0.5f);
      outline.lineTo(1.0f, 0.5f);
      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.2f);
      return path;
    }

    static Path bandPass() {
      static constexpr float kMiddle = 3.0f / 5.0f;
      static constexpr float kBottom = 4.0f / 5.0f;

      Path outline;
      outline.startNewSubPath(0.0f, kBottom);
      outline.lineTo(1.0f / 3.0f, kMiddle);
      outline.lineTo(0.5f, 0.25f);
      outline.lineTo(2.0f / 3.0f, kMiddle);
      outline.lineTo(1.0f, kBottom);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.2f);
      return path;
    }

    static Path leftArrow() {
      static constexpr float kArrowAmount = 1.0f / 3.0f;
      static constexpr float kBuffer = 0.0f;

      Path outline;
      outline.startNewSubPath(1.0f - kBuffer, 0.5f);
      outline.lineTo(kBuffer, 0.5f);
      outline.startNewSubPath(kBuffer, 0.5f);
      outline.lineTo(kBuffer + kArrowAmount, 0.5f - kArrowAmount);
      outline.startNewSubPath(kBuffer, 0.5f);
      outline.lineTo(kBuffer + kArrowAmount, 0.5f + kArrowAmount);
      return createFilterStroke(outline);
    }

    static Path rightArrow() {
      static constexpr float kArrowAmount = 1.0f / 3.0f;
      static constexpr float kBuffer = 0.0f;

      Path outline;
      outline.startNewSubPath(1.0f - kBuffer, 0.5f);
      outline.lineTo(kBuffer, 0.5f);
      outline.startNewSubPath(1.0f - kBuffer, 0.5f);
      outline.lineTo(1.0f - kArrowAmount - kBuffer, 0.5f - kArrowAmount);
      outline.startNewSubPath(1.0f - kBuffer, 0.5f);
      outline.lineTo(1.0f - kArrowAmount - kBuffer, 0.5f + kArrowAmount);
      return createFilterStroke(outline);
    }

    static Path phaser1() {
      Path outline;
      outline.startNewSubPath(0.0f, 0.5f);
      outline.lineTo(1.0f / 3.0f, 3.0f / 4.0f);
      outline.lineTo(1.0f / 2.0f, 1.0f / 4.0f);
      outline.lineTo(2.0f / 3.0f, 3.0f / 4.0f);
      outline.lineTo(1.0f, 0.5f);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.15f, 1.0f, 0.15f), 0.1f);
      path.addLineSegment(Line<float>(1.0f, 0.85f, 1.0f, 0.85f), 0.1f);
      return path;
    }

    static Path phaser3() {
      static constexpr int kNumHumps = 5;

      static const float kUp = 1.0f / 4.0f;
      static const float kDown = 3.0f / 4.0f;

      float delta = 1.0f / (2 * kNumHumps + 2);
      Path outline;
      outline.startNewSubPath(0.0f, 0.5f);

      float position = 0.0f;
      for (int i = 0; i < kNumHumps; ++i) {
        position += delta;
        outline.lineTo(position, kDown);
        position += delta;
        outline.lineTo(position, kUp);
      }
      position += delta;
      outline.lineTo(position, kDown);
      outline.lineTo(1.0f, 0.5f);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.15f, 1.0f, 0.15f), 0.1f);
      path.addLineSegment(Line<float>(1.0f, 0.85f, 1.0f, 0.85f), 0.1f);
      return path;
    }

    static Path notch() {
      static constexpr float kTop = 2.0f / 5.0f;
      static constexpr float kBottom = 4.0f / 5.0f;

      Path outline;
      outline.startNewSubPath(0.0f, kTop);
      outline.lineTo(1.0f / 3.0f, kTop);
      outline.lineTo(1.0f / 2.0f, kBottom);
      outline.lineTo(2.0f / 3.0f, kTop);
      outline.lineTo(1.0f, kTop);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.1f);
      return path;
    }

    static Path narrowBand() {
      static constexpr float kTop = 2.0f / 5.0f;
      static constexpr float kBottom = 4.0f / 5.0f;

      Path outline;
      outline.startNewSubPath(0.0f, kBottom);
      outline.lineTo(1.0f / 3.0f, kBottom);
      outline.lineTo(0.5f, kTop);
      outline.lineTo(2.0f / 3.0f, kBottom);
      outline.lineTo(1.0f, kBottom);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.1f);
      return path;
    }

    static Path microphoneIcon() {
      // Microphone icon in 0..1 space
      // Capsule (rounded rect body)
      Path path;
      float capW = 0.30f;
      float capH = 0.42f;
      float capX = 0.5f - capW * 0.5f;
      float capY = 0.12f;
      float capR = capW * 0.5f;
      path.addRoundedRectangle(capX, capY, capW, capH, capR);

      // Pickup arc (U-shape around capsule)
      float arcStroke = 0.06f;
      float arcW = 0.48f;
      float arcH = 0.52f;
      float arcX = 0.5f - arcW * 0.5f;
      float arcY = 0.14f;
      Path arcOutline;
      arcOutline.addArc(arcX, arcY, arcW, arcH, 0.0f, vital::kPi, true);
      PathStrokeType arcStrokeType(arcStroke, PathStrokeType::curved, PathStrokeType::butt);
      Path arcPath;
      arcStrokeType.createStrokedPath(arcPath, arcOutline);
      path.addPath(arcPath);

      // Vertical stem
      float stemW = 0.07f;
      float stemTop = 0.62f;
      float stemBot = 0.78f;
      path.addRectangle(0.5f - stemW * 0.5f, stemTop, stemW, stemBot - stemTop);

      // Horizontal base
      float baseW = 0.28f;
      float baseH = 0.06f;
      path.addRectangle(0.5f - baseW * 0.5f, stemBot - baseH * 0.5f, baseW, baseH);

      // Bounding points
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.2f);
      path.addLineSegment(Line<float>(1.0f, 1.0f, 1.0f, 1.0f), 0.2f);
      return path;
    }

    static Path microphoneIcon2() {
      static const char svg[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 90 90\">"
        "<path d=\"M 45 70.968 c -16.013 0 -29.042 -13.028 -29.042 -29.042 c 0 -1.712 1.388 -3.099 "
        "3.099 -3.099 c 1.712 0 3.099 1.388 3.099 3.099 C 22.157 54.522 32.404 64.77 45 64.77 "
        "c 12.595 0 22.843 -10.248 22.843 -22.843 c 0 -1.712 1.387 -3.099 3.099 -3.099 "
        "s 3.099 1.388 3.099 3.099 C 74.042 57.94 61.013 70.968 45 70.968 z\" fill=\"#ffffff\"/>"
        "<path d=\"M 45 60.738 c -9.2565 0 -16.83 -8.415 -16.83 -18.7 V 18.7 C 28.17 8.415 35.7435 0 45 0 "
        "c 9.2565 0 16.83 8.415 16.83 18.7 v 23.337 C 61.83 52.322 54.2565 60.738 45 60.738 z\" fill=\"#ffffff\"/>"
        "<path d=\"M 45 89.213 c -1.712 0 -3.099 -1.387 -3.099 -3.099 V 68.655 c 0 -1.712 1.388 -3.099 "
        "3.099 -3.099 c 1.712 0 3.099 1.387 3.099 3.099 v 17.459 C 48.099 87.826 46.712 89.213 45 89.213 z\" fill=\"#ffffff\"/>"
        "<path d=\"M 55.451 90 H 34.549 c -1.712 0 -3.099 -1.387 -3.099 -3.099 s 1.388 -3.099 3.099 -3.099 "
        "h 20.901 c 1.712 0 3.099 1.387 3.099 3.099 S 57.163 90 55.451 90 z\" fill=\"#ffffff\"/>"
        "</svg>";
      Path path = fromSvgData(svg, sizeof(svg) - 1);
      // Squeeze horizontally to make the mic body thinner
      static constexpr float kMicBodyWidthScale = 0.9f;
      path.applyTransform(AffineTransform::scale(kMicBodyWidthScale, 1.0f)
                            .translated(90.0f * (1.0f - kMicBodyWidthScale) * 0.5f, 0.0f));
      return path;
    }

    static Path sendArrowIcon() {
      static const char svg[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 24 24\">"
        "<path fill-rule=\"evenodd\" clip-rule=\"evenodd\" d=\"M12 3C12.2652 3 12.5196 3.10536 "
        "12.7071 3.29289L19.7071 10.2929C20.0976 10.6834 20.0976 11.3166 19.7071 11.7071C19.3166 "
        "12.0976 18.6834 12.0976 18.2929 11.7071L13 6.41421V20C13 20.5523 12.5523 21 12 21C11.4477 "
        "21 11 20.5523 11 20V6.41421L5.70711 11.7071C5.31658 12.0976 4.68342 12.0976 4.29289 "
        "11.7071C3.90237 11.3166 3.90237 10.6834 4.29289 10.2929L11.2929 3.29289C11.4804 3.10536 "
        "11.7348 3 12 3Z\" fill=\"#ffffff\"/>"
        "</svg>";
      return fromSvgData(svg, sizeof(svg) - 1);
    }

    static Path stopIcon() {
      Path path;
      float r = 0.12f;
      float x1 = 0.22f, y1 = 0.22f;
      float x2 = 0.78f, y2 = 0.78f;

      path.startNewSubPath(x1 + r, y1);
      path.lineTo(x2 - r, y1);
      path.quadraticTo(x2, y1, x2, y1 + r);
      path.lineTo(x2, y2 - r);
      path.quadraticTo(x2, y2, x2 - r, y2);
      path.lineTo(x1 + r, y2);
      path.quadraticTo(x1, y2, x1, y2 - r);
      path.lineTo(x1, y1 + r);
      path.quadraticTo(x1, y1, x1 + r, y1);
      path.closeSubPath();

      return path;
    }

    static Path clearXIcon() {
      static const char svg[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 24 24\">"
        "<path d=\"M18.7 5.3a1.5 1.5 0 0 0-2.12 0L12 9.88 7.42 5.3a1.5 1.5 0 0 0-2.12 2.12"
        "L9.88 12 5.3 16.58a1.5 1.5 0 0 0 2.12 2.12L12 14.12l4.58 4.58a1.5 1.5 0 0 0 2.12-2.12"
        "L14.12 12l4.58-4.58a1.5 1.5 0 0 0 0-2.12z\" fill=\"#ffffff\"/>"
        "</svg>";
      Path path = fromSvgData(svg, sizeof(svg) - 1);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.01f);
      path.addLineSegment(Line<float>(24.0f, 24.0f, 24.0f, 24.0f), 0.01f);
      return path;
    }

    static Path cancelEditXIcon() {
      static const char svg[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 24 24\">"
        "<path d=\"M18.7 5.3a1.2 1.2 0 0 0-1.7 0L12 10.3 7 5.3a1.2 1.2 0 0 0-1.7 1.7"
        "L10.3 12 5.3 17a1.2 1.2 0 0 0 1.7 1.7L12 13.7l5 5a1.2 1.2 0 0 0 1.7-1.7"
        "L13.7 12l5-5a1.2 1.2 0 0 0 0-1.7z\" fill=\"#ffffff\"/>"
        "</svg>";
      Path path = fromSvgData(svg, sizeof(svg) - 1);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.01f);
      path.addLineSegment(Line<float>(24.0f, 24.0f, 24.0f, 24.0f), 0.01f);
      return path;
    }

    static Path wideBand() {
      static constexpr float kTop = 2.0f / 5.0f;
      static constexpr float kBottom = 4.0f / 5.0f;

      Path outline;
      outline.startNewSubPath(0.0f, kBottom);
      outline.lineTo(1.0f / 3.0f, kTop);
      outline.lineTo(2.0f / 3.0f, kTop);
      outline.lineTo(1.0f, kBottom);

      Path path = createFilterStroke(outline);
      path.addLineSegment(Line<float>(1.0f, 0.2f, 1.0f, 0.2f), 0.1f);
      return path;
    }
};

