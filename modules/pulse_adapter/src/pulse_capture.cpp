//
// Created by kira on 07.04.2021.
//

#include "pulse_adapter/pulse_capture.hpp"

#include <endian.h>
#include <pulse/simple.h>

#include "pulse_adapter/pulse_exception.hpp"

namespace audio {
PulseCapture::PulseCapture(const PulseDevice& device, uint32_t frequency, uint8_t channels) {
    pa_sample_spec sample_spec{};
    if constexpr (BYTE_ORDER == LITTLE_ENDIAN) {
        sample_spec = pa_sample_spec{PA_SAMPLE_FLOAT32LE, frequency, channels};
    } else {
        sample_spec = {PA_SAMPLE_FLOAT32BE, frequency, channels};
    }

    int error_code = 0;
    simple_ = pa_simple_new(nullptr, "player_usage", PA_STREAM_RECORD, device.name.c_str(),
                            "record", &sample_spec, nullptr, nullptr, &error_code);
    if (error_code) {
        throw PulseException{"pa_simple_new", error_code};
    }
}

PulseCapture::~PulseCapture() { pa_simple_free(simple_); }

void PulseCapture::fill_sample(std::vector<float>& buf) {
    int error_code = 0;
    if (pa_simple_read(simple_, buf.data(), buf.size() * sizeof(float), &error_code) < 0) {
        throw PulseException{"pa_simple_read", error_code};
    }
}
}  // namespace audio
