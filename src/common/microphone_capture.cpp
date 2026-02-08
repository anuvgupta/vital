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

#include "microphone_capture.h"

// mic_permission_mac.mm provides this (compiled separately to avoid ObjC/JUCE header conflicts)
#if JUCE_MAC
extern bool requestMicrophonePermission();
#endif

MicrophoneCapture::MicrophoneCapture() {
  // Pre-allocate buffers for worst case: 4096 samples at 48kHz -> ~1365 at 16kHz
  resample_buffer_.resize(8192, 0.0f);
  conversion_buffer_.resize(8192, 0);
}

MicrophoneCapture::~MicrophoneCapture() {
  stopCapture();
}

bool MicrophoneCapture::startCapture(AudioDataCallback callback, SilenceCallback on_silence) {
  if (capturing_.load())
    stopCapture();

  audio_callback_ = std::move(callback);
  silence_callback_ = std::move(on_silence);
  silent_callback_count_ = 0;
  silence_threshold_callbacks_ = 0;
  silence_fired_.store(false);

#if JUCE_MAC
  if (!requestMicrophonePermission()) {
    DBG("MicrophoneCapture: Microphone permission not granted");
    return false;
  }
#endif

  // Initialize with 1 input, 0 outputs
  auto result = device_manager_.initialise(1, 0, nullptr, true);
  if (result.isNotEmpty()) {
    DBG("MicrophoneCapture: Failed to initialize audio device: " + result);
    return false;
  }

  device_manager_.addAudioCallback(this);
  capturing_.store(true);
  DBG("MicrophoneCapture: Started capturing");
  return true;
}

void MicrophoneCapture::stopCapture() {
  if (!capturing_.load())
    return;

  capturing_.store(false);
  device_manager_.removeAudioCallback(this);
  device_manager_.closeAudioDevice();
  audio_callback_ = nullptr;
  silence_callback_ = nullptr;
  silent_callback_count_ = 0;
  silence_fired_.store(false);
  resampler_.reset();
  DBG("MicrophoneCapture: Stopped capturing");
}

void MicrophoneCapture::audioDeviceAboutToStart(AudioIODevice* device) {
  device_sample_rate_ = device->getCurrentSampleRate();
  resampler_.reset();

  float timeout_seconds = LoadSave::getMicSilenceTimeout();
  int block_size = device->getCurrentBufferSizeSamples();
  if (timeout_seconds > 0.0f && block_size > 0 && device_sample_rate_ > 0.0) {
    double callbacks_per_sec = device_sample_rate_ / block_size;
    silence_threshold_callbacks_ = static_cast<int>(callbacks_per_sec * timeout_seconds);
  } else {
    silence_threshold_callbacks_ = 0;  // disabled
  }
  silent_callback_count_ = 0;
  silence_fired_.store(false);
  DBG("MicrophoneCapture: Device started at " + String(device_sample_rate_) + " Hz"
      + " device=\"" + device->getName() + "\""
      + " type=\"" + device->getTypeName() + "\""
      + " inputChannels=" + String(device->getActiveInputChannels().countNumberOfSetBits())
      + " inputNames=" + device->getInputChannelNames().joinIntoString(","));
}

void MicrophoneCapture::audioDeviceStopped() {
  device_sample_rate_ = 0.0;
}

void MicrophoneCapture::audioDeviceIOCallback(const float** inputChannelData,
                                              int numInputChannels,
                                              float** /*outputChannelData*/,
                                              int /*numOutputChannels*/,
                                              int numSamples) {
  if (!capturing_.load() || !audio_callback_ || numInputChannels < 1 || inputChannelData[0] == nullptr) {
    static int skip_log = 0;
    if (skip_log++ % 500 == 0)
      DBG("MicrophoneCapture::audioDeviceIOCallback: skipping (capturing=" + String((int)capturing_.load())
          + " callback=" + String(audio_callback_ ? "yes" : "no")
          + " channels=" + String(numInputChannels) + ")");
    return;
  }

  const float* input = inputChannelData[0];

  if (device_sample_rate_ <= 0.0)
    return;

  // Calculate how many output samples we'll get after resampling
  double speed_ratio = device_sample_rate_ / static_cast<double>(kTargetSampleRate);
  int num_output_samples = static_cast<int>(numSamples / speed_ratio);

  if (num_output_samples <= 0)
    return;

  // Ensure buffers are large enough (no allocation on audio thread if pre-sized correctly)
  if (static_cast<int>(resample_buffer_.size()) < num_output_samples)
    return;  // Buffer too small, skip this block rather than allocate
  if (static_cast<int>(conversion_buffer_.size()) < num_output_samples)
    return;

  // Find peak amplitude in raw input (needed for silence detection + logging)
  float peak = 0.0f;
  for (int i = 0; i < numSamples; ++i) {
    float abs_val = std::abs(input[i]);
    if (abs_val > peak) peak = abs_val;
  }

  // Silence detection
  if (peak < kSilenceThreshold) {
    ++silent_callback_count_;
    if (silence_threshold_callbacks_ > 0 &&
        silent_callback_count_ >= silence_threshold_callbacks_ &&
        !silence_fired_.load() && silence_callback_) {
      silence_fired_.store(true);
      auto cb = silence_callback_;
      MessageManager::callAsync([cb]() { cb(); });
    }
  } else {
    silent_callback_count_ = 0;
  }

  // Periodic log
  static int callback_count = 0;
  if (callback_count++ % 200 == 0) {
    DBG("MicrophoneCapture: audio callback #" + String(callback_count)
        + " numSamples=" + String(numSamples)
        + " outputSamples=" + String(num_output_samples)
        + " ratio=" + String(speed_ratio)
        + " inputPeak=" + String(peak, 6)
        + " silentCount=" + String(silent_callback_count_) + "/" + String(silence_threshold_callbacks_));
  }

  if (std::abs(speed_ratio - 1.0) < 0.001) {
    // No resampling needed (device already at 16kHz)
    for (int i = 0; i < numSamples; ++i) {
      float clamped = jlimit(-1.0f, 1.0f, input[i]);
      conversion_buffer_[static_cast<size_t>(i)] = static_cast<int16_t>(clamped * 32767.0f);
    }
    audio_callback_(conversion_buffer_.data(), numSamples * static_cast<int>(sizeof(int16_t)));
  } else {
    // Resample from device rate to 16kHz
    resampler_.process(speed_ratio, input, resample_buffer_.data(), num_output_samples);

    // Convert float to int16 (linear16)
    for (int i = 0; i < num_output_samples; ++i) {
      float clamped = jlimit(-1.0f, 1.0f, resample_buffer_[static_cast<size_t>(i)]);
      conversion_buffer_[static_cast<size_t>(i)] = static_cast<int16_t>(clamped * 32767.0f);
    }

    // Log resampled output periodically
    if (callback_count % 200 == 1) {
      float resampled_peak = 0.0f;
      for (int i = 0; i < num_output_samples; ++i) {
        float abs_val = std::abs(resample_buffer_[static_cast<size_t>(i)]);
        if (abs_val > resampled_peak) resampled_peak = abs_val;
      }
      int16_t int16_peak = 0;
      for (int i = 0; i < num_output_samples; ++i) {
        int16_t abs_val = std::abs(conversion_buffer_[static_cast<size_t>(i)]);
        if (abs_val > int16_peak) int16_peak = abs_val;
      }
      DBG("MicrophoneCapture: resampledPeak=" + String(resampled_peak, 6)
          + " int16Peak=" + String(int16_peak));
    }

    audio_callback_(conversion_buffer_.data(), num_output_samples * static_cast<int>(sizeof(int16_t)));
  }
}
