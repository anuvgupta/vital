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
#include <functional>
#include <atomic>
#include <vector>

class MicrophoneCapture : private AudioIODeviceCallback {
  public:
    static constexpr int kTargetSampleRate = 16000;
    static constexpr float kSilenceThreshold = 0.06f;
    static constexpr float kDefaultSilenceTimeoutSeconds = 2.5f;

    using AudioDataCallback = std::function<void(const void* data, int num_bytes)>;
    using SilenceCallback = std::function<void()>;

    MicrophoneCapture();
    ~MicrophoneCapture();

    // silence_timeout_override: if > 0, overrides the user-configured silence timeout
    bool startCapture(AudioDataCallback callback, SilenceCallback on_silence = nullptr,
                      float silence_timeout_override = -1.0f);
    void stopCapture();
    bool isCapturing() const { return capturing_.load(); }

  private:
    void audioDeviceIOCallback(const float** inputChannelData,
                               int numInputChannels,
                               float** outputChannelData,
                               int numOutputChannels,
                               int numSamples) override;
    void audioDeviceAboutToStart(AudioIODevice* device) override;
    void audioDeviceStopped() override;

    AudioDeviceManager device_manager_;
    AudioDataCallback audio_callback_;
    SilenceCallback silence_callback_;
    std::atomic<bool> capturing_{false};

    double device_sample_rate_ = 0.0;
    LagrangeInterpolator resampler_;
    std::vector<float> resample_buffer_;
    std::vector<int16_t> conversion_buffer_;

    int silent_callback_count_ = 0;
    int silence_threshold_callbacks_ = 0;
    std::atomic<bool> silence_fired_{false};
    float silence_timeout_override_ = -1.0f;
};
