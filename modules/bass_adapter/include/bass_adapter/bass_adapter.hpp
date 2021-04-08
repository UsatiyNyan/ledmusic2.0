//
// Created by kira on 06.04.2021.
//

#pragma once

#include <bass/bass.h>

#include <string>

#include "pulse_adapter/pulse_capture.hpp"

namespace audio {
enum class BassData : uint32_t {
    FFT256 = BASS_DATA_FFT256,
    FFT512 = BASS_DATA_FFT512,
    FFT1024 = BASS_DATA_FFT1024,
    FFT2048 = BASS_DATA_FFT2048,
    FFT4096 = BASS_DATA_FFT4096,
    FFT8192 = BASS_DATA_FFT8192,
    FFT16384 = BASS_DATA_FFT16384,
    FFT32768 = BASS_DATA_FFT32768
};

class BassAdapter {
public:
    constexpr static size_t CAPTURE_BUFFER_SIZE = 2048;

    explicit BassAdapter(const PulseDevice& device,
                         uint32_t frequency = PulseCapture::DEFAULT_FREQUENCY,
                         uint8_t channels = PulseCapture::DEFAULT_CHANNELS);
    ~BassAdapter();

    void process_sample(std::vector<float>& sample_buffer);

private:
    HSTREAM stream_descriptor_;
    PulseCapture capture_;
    std::vector<float> capture_buffer_;
};
}  // namespace audio
