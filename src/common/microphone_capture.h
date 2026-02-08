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

    using AudioDataCallback = std::function<void(const void* data, int num_bytes)>;

    MicrophoneCapture();
    ~MicrophoneCapture();

    bool startCapture(AudioDataCallback callback);
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
    std::atomic<bool> capturing_{false};

    double device_sample_rate_ = 0.0;
    LagrangeInterpolator resampler_;
    std::vector<float> resample_buffer_;
    std::vector<int16_t> conversion_buffer_;
};
