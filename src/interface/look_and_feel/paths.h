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
        "<svg version=\"1.2\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 541 519\" width=\"541\" height=\"519\">"
        "<path fill=\"#ffffff\" d=\"m18.5 2.48c-3.3 1.4-7.3 3.78-8.88 5.28-1.58 1.51-4.4 5.1-6.25 7.99l-3.37 "
        "5.25c0.49 197.67 0.57 201.63 2.4 205 1.05 1.93 2.85 4.77 4 6.33 1.16 1.55 4.13 4.15 6.6 5.77 "
        "3.22 2.11 5.71 2.94 8.75 2.92 2.34-0.01 4.48 0.43 4.75 0.98 0.33 0.66 33.67 1 97 1 63.33 0 "
        "96.67-0.34 97-1 0.28-0.55 2.19-0.98 4.25-0.96 2.63 0.03 5.25-0.96 8.75-3.29 4-2.66 5.77-4.82 "
        "8.84-10.79 3.54-6.89 3.8-7.92 3.28-13.46-0.39-4.16-1.38-7.23-3.23-10-1.47-2.2-17.46-18.74"
        "-35.53-36.75l-32.86-32.75c6.72-5.81 12.68-10.17 17.59-13.43 4.9-3.27 13.19-8.08 18.41-10.69 "
        "5.22-2.61 14.22-6.33 20-8.26 5.78-1.93 15-4.48 20.5-5.67 7.64-1.65 14.72-2.28 30-2.66 17.08"
        "-0.43 21.75-0.21 32 1.53 6.6 1.12 17.18 3.67 23.5 5.68 6.32 2.01 17.35 6.54 24.5 10.07 7.15 "
        "3.52 17.27 9.44 22.5 13.14 5.23 3.7 15.15 12.37 22.05 19.26 7.6 7.59 15.28 16.47 19.49 22.53 "
        "3.81 5.5 9.44 14.95 12.5 21 3.06 6.05 7.21 15.95 9.22 22 2.02 6.05 4.67 15.5 5.9 21 1.95 "
        "8.71 2.24 12.96 2.29 33 0.04 20.52-0.2 24.18-2.31 34-1.3 6.05-3.91 15.5-5.8 21-1.88 5.5"
        "-5.86 14.95-8.83 21-2.97 6.05-8.5 15.5-12.29 21-3.79 5.5-10.95 14.27-15.91 19.5-4.97 5.23"
        "-12.13 12.04-15.92 15.14-3.79 3.1-10.5 8.05-14.9 11-4.41 2.95-13.19 7.91-19.5 11.03-6.32 "
        "3.11-15.76 7.04-20.99 8.73-5.23 1.69-13.55 4.01-18.5 5.14-6.5 1.5-14.14 2.23-27.5 2.66"
        "-11.97 0.38-22.03 0.16-28.5-0.62-5.5-0.67-14.39-2.31-19.75-3.65-5.36-1.33-13.91-4.07-19"
        "-6.07-5.09-1.99-12.4-5.2-16.25-7.12-3.85-1.91-10.82-5.96-15.5-8.99-4.68-3.03-11.88-8.32-16"
        "-11.75-4.13-3.43-12.68-11.69-19-18.34-11.15-11.74-11.63-12.1-15.75-12.13-3.85-0.03-4.98 "
        "0.62-12 6.82-4.26 3.77-15.74 15.02-25.5 25-13.49 13.79-17.9 18.93-18.38 21.4-0.44 2.26 0 "
        "4.62 1.45 7.75 1.32 2.86 6.75 9.2 14.88 17.38 7.04 7.08 16.4 15.78 20.8 19.33 4.4 3.55 "
        "13.62 10.21 20.5 14.79 6.87 4.59 16.32 10.37 21 12.83 4.68 2.47 12.55 6.17 17.5 8.23 4.95 "
        "2.05 14.62 5.64 21.5 7.97 6.87 2.33 17.68 5.39 24 6.8 6.32 1.4 16 3.3 21.5 4.21 8.24 1.37 "
        "15.19 1.58 39.5 1.22 27.25-0.4 30.49-0.64 42.5-3.15 7.15-1.49 18.4-4.3 25-6.24 6.6-1.94 "
        "17.62-5.78 24.5-8.52 6.87-2.74 17.23-7.52 23-10.61 5.77-3.09 16.35-9.53 23.5-14.31 7.15"
        "-4.78 17.05-12.22 22-16.54 4.95-4.31 12.34-11.22 16.41-15.36 4.08-4.14 10.78-11.35 14.88"
        "-16.03 4.11-4.68 11.49-14.57 16.4-22 4.92-7.43 11.79-19.13 15.26-26 3.48-6.88 8.36-17.68 "
        "10.84-24 2.48-6.32 6.12-17.35 8.09-24.5 1.96-7.15 4.49-18.18 5.63-24.5 1.13-6.32 2.58"
        "-18.93 3.22-28 0.89-12.59 0.89-20.06 0-31.5-0.64-8.25-1.86-19.05-2.71-24-0.85-4.95-2.94"
        "-14.63-4.64-21.5-1.7-6.88-5.34-18.57-8.1-26-2.76-7.43-7.61-18.68-10.78-25-3.16-6.32-8.34"
        "-15.78-11.51-21-3.17-5.22-8.93-13.78-12.82-19-3.88-5.22-11.58-14.41-17.11-20.42-5.53-6"
        "-15.01-15.16-21.06-20.35-6.05-5.19-14.38-11.82-18.5-14.72-4.13-2.9-11.77-7.83-17-10.96"
        "-5.23-3.12-14-7.84-19.5-10.49-5.5-2.65-13.38-6.16-17.5-7.8-4.13-1.63-12-4.36-17.5-6.05"
        "-5.5-1.69-13.6-3.98-18-5.08-4.4-1.11-12.05-2.77-17-3.71-6.71-1.27-16.49-1.81-38.5-2.14"
        "-26.39-0.39-30.71-0.23-41 1.58-6.32 1.11-17.57 3.58-25 5.48-7.43 1.9-19.35 5.72-26.5 8.49"
        "-7.15 2.76-15.7 6.26-19 7.76-3.3 1.51-10.05 4.98-15 7.71-4.95 2.73-12.6 7.33-17 10.22-4.4 "
        "2.89-13.18 9.36-19.5 14.38-6.33 5.02-11.95 9.11-12.5 9.08-0.55-0.02-10.22-9.33-21.5-20.68"
        "-11.28-11.35-26.8-26.48-34.5-33.61-7.7-7.14-15.58-14.05-17.5-15.35-2.19-1.48-5.56-2.56-9"
        "-2.89-4.44-0.42-6.65-0.03-11.5 2.03z\"/>"
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
      static constexpr float kMicBodyWidthScale = 0.98f;
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
        "<path d=\"M18.7 5.3a1.5 1.5 0 0 0-2.12 0L12 9.88 7.42 5.3a1.5 1.5 0 0 0-2.12 2.12"
        "L9.88 12 5.3 16.58a1.5 1.5 0 0 0 2.12 2.12L12 14.12l4.58 4.58a1.5 1.5 0 0 0 2.12-2.12"
        "L14.12 12l4.58-4.58a1.5 1.5 0 0 0 0-2.12z\" fill=\"#ffffff\"/>"
        "</svg>";
      Path path = fromSvgData(svg, sizeof(svg) - 1);
      path.addLineSegment(Line<float>(0.0f, 0.0f, 0.0f, 0.0f), 0.01f);
      path.addLineSegment(Line<float>(24.0f, 24.0f, 24.0f, 24.0f), 0.01f);
      return path;
    }

    static Path speechWaveformIcon() {
      static const char svg[] =
        "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 445 347\">"
        "<path fill-rule=\"evenodd\" d=\"m223.5 0.16c97.4-0.09 151.08 0.21 157 0.9 5.04 0.59 11.86 2.18 "
        "15.5 3.63 3.57 1.42 9.65 4.44 13.5 6.7 3.85 2.26 9.96 7.03 13.59 10.61 3.62 3.58 8.45 9.65 "
        "10.74 13.5 2.29 3.85 5.7 11.5 11.01 27l-0.47 66c-0.37 53.14-0.75 67.46-1.95 73.5-0.83 4.13"
        "-3.04 10.65-4.92 14.5-1.89 3.85-5.63 9.93-8.32 13.5-2.69 3.57-7.54 8.64-10.78 11.26-3.25 "
        "2.62-10.4 7-15.9 9.72-5.5 2.73-12.02 5.45-14.5 6.05-2.99 0.72-38.33 1.28-206.5 2.27l-41.5 "
        "40.77c-22.83 22.42-43.05 42.04-44.94 43.6-2.89 2.38-4.36 2.83-9.18 2.83-4.17 0-6.47-0.55"
        "-8.44-2-1.48-1.1-3.65-3.27-4.82-4.82-2.06-2.75-2.13-3.83-2.37-41.75-0.23-36.13-0.38-38.96"
        "-2-39.36-0.96-0.23-3.78-0.71-6.25-1.07-2.48-0.35-7.42-1.57-11-2.71-3.58-1.14-8.53-3.07-11"
        "-4.3-2.48-1.23-7.42-4.55-11-7.37-3.58-2.82-8.89-7.94-11.82-11.37-2.92-3.44-7.05-9.85-9.18"
        "-14.25-2.12-4.4-4.65-10.7-5.6-14-1.55-5.36-1.78-13.2-2.6-141l2.49-7c1.38-3.85 3.59-9.48 "
        "4.92-12.5 1.32-3.03 3.78-7.53 5.45-10 1.67-2.48 6.14-7.6 9.94-11.39 3.79-3.79 9.82-8.61 "
        "13.4-10.71 3.57-2.1 9.65-5.02 13.5-6.5 4.82-1.85 9.96-2.9 16.5-3.39 5.22-0.39 76.1-0.77 "
        "157.5-0.85zm21.31 39.99l0.19 179.85c4.26 3.15 6.31 4.05 7.3 4.03 0.98-0.01 2.9-1.15 4.25"
        "-2.53l2.45-2.5v-178c-3.88-3.88-5.83-5-6.85-5-1.01 0-3.08 0.93-4.59 2.07zm-86.72 29.77l"
        "-0.09 120.09c3.87 3.87 5.92 5 7.04 5 1.13 0 3.15-1.13 4.5-2.5l2.46-2.5c0-105.11-0.29"
        "-119.58-1.25-121.49-0.69-1.37-2.15-2.71-3.25-2.99-1.1-0.27-2.59-0.5-3.3-0.51-0.71-0.01"
        "-2.38 1.09-3.7 2.44zm57.7 0.36c0.14 117.95 0.18 119.29 2.17 121.98 1.44 1.94 2.92 2.75 "
        "5.04 2.75 2.11 0 3.6-0.81 5.03-2.75 1.99-2.69 2.04-3.98 2.04-62.25 0-58.27-0.05-59.55"
        "-2.04-62.25-1.41-1.91-2.93-2.75-4.97-2.75q-2.93 0-5.1 2.64zm59.41-1.73c-0.9 1.84-1.2 "
        "17.57-1.2 61.96v59.5c3.87 3.87 5.92 5 7.04 5 1.13 0 3.15-1.13 4.5-2.5l2.46-2.5v-120c"
        "-3.88-3.88-5.79-4.95-6.75-4.89-0.97 0.07-2.45 0.31-3.3 0.55-0.85 0.24-2.09 1.54-2.75 "
        "2.88zm-146.33 61.84c0.07 31.01 0.08 31.13 2.35 33.35 1.25 1.22 3.4 2.25 4.78 2.29 1.37 "
        "0.03 3.62-0.82 5-1.89l2.5-1.95c0.45-46.25 0.34-60.69 0.04-61.93-0.3-1.24-1.44-3.15-2.54"
        "-4.25-1.1-1.1-3.32-2-4.94-2q-2.93 0-5.1 2.63c-2.13 2.59-2.17 3.25-2.09 33.75zm58.22"
        "-31.47l-0.09 62.09c3.87 3.87 6.01 5.01 7.25 5.02 1.23 0.02 3.25-0.99 4.48-2.25 2.2-2.25 "
        "2.22-2.57 2.27-33.77 0.05-31.48 0.05-31.5-2.23-33.73-1.25-1.23-3.31-2.24-4.57-2.25-1.26"
        "-0.01-3.38 1.08-4.7 2.43zm115.36 1.34c-0.3 1.24-0.41 15.68-0.25 32.09l0.3 29.84c3.87 "
        "3.03 6.23 3.89 7.75 3.87 1.8-0.03 3.44-0.99 4.78-2.8 1.94-2.62 2.03-4.14 2.03-33.25 "
        "0-29.1-0.09-30.62-2.03-33.25-1.43-1.93-2.92-2.75-5.03-2.75-1.67 0-3.89 0.89-5 2-1.1 "
        "1.1-2.25 3.02-2.55 4.25z\" fill=\"#ffffff\"/>"
        "</svg>";
      return fromSvgData(svg, sizeof(svg) - 1);
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

