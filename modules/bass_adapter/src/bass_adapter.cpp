//
// Created by kira on 06.04.2021.
//

#include "bass_adapter/bass_adapter.hpp"

#include "bass_adapter/bass_exception.hpp"

namespace {
audio::BassData bass_data_fft_from_sample_size(size_t sample_size) {
    switch (sample_size) {
        case 128:
            return audio::BassData::FFT256;
        case 256:
            return audio::BassData::FFT512;
        case 512:
            return audio::BassData::FFT1024;
        case 1024:
            return audio::BassData::FFT2048;
        case 2048:
            return audio::BassData::FFT4096;
        case 4096:
            return audio::BassData::FFT8192;
        case 8192:
            return audio::BassData::FFT16384;
        case 16384:
            return audio::BassData::FFT32768;
        default:
            throw audio::BassException{"incorrect sample_size"};
    }
}
}  // namespace

namespace audio {
BassAdapter::BassAdapter(const PulseDevice& device, uint32_t frequency, uint8_t channels)
    : capture_{device, frequency, channels} {
    capture_buffer_.assign(CAPTURE_BUFFER_SIZE, 0);
    if (!BASS_Init(0, frequency, BASS_DEVICE_LOOPBACK, nullptr, nullptr)) {
        throw BassException{"BASS_Init"};
    }
    stream_descriptor_ = BASS_StreamCreate(
        frequency, channels, BASS_STREAM_DECODE | BASS_SAMPLE_FLOAT, STREAMPROC_PUSH, nullptr);
    if (!stream_descriptor_) {
        throw BassException{"BASS_StreamCreate"};
    }
}

BassAdapter::~BassAdapter() { BASS_Free(); }

void BassAdapter::process_sample(std::vector<float>& sample_buffer) {
    if (capture_buffer_.size() != sample_buffer.size()) {
        throw BassException{"sample buffer(size: " + std::to_string(sample_buffer.size()) +
                            ") and capture buffer(size: " + std::to_string(capture_buffer_.size()) +
                            ") don't match"};
    }
    capture_.fill_sample(capture_buffer_);
    if (BASS_StreamPutData(stream_descriptor_, capture_buffer_.data(),
                           capture_buffer_.size() * sizeof(float)) == -1u) {
        throw BassException{"BASS_StreamPutData"};
    }
    if (BASS_ChannelGetData(
            stream_descriptor_, sample_buffer.data(),
            static_cast<uint32_t>(bass_data_fft_from_sample_size(sample_buffer.size()))) == -1u) {
        throw BassException{"BASS_ChannelGetData"};
    }
}
}  // namespace audio
