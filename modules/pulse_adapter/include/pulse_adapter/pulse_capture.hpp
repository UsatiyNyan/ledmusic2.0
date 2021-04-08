//
// Created by kira on 07.04.2021.
//

#pragma once

#include <pulse/simple.h>

#include <string>
#include <vector>

#include "pulse_device.hpp"

namespace audio {
class PulseCapture {
public:
    constexpr static uint32_t DEFAULT_FREQUENCY = 44100u;
    constexpr static uint8_t DEFAULT_CHANNELS = 2u;

    explicit PulseCapture(const PulseDevice& device, uint32_t frequency = DEFAULT_FREQUENCY,
                          uint8_t channels = DEFAULT_CHANNELS);
    ~PulseCapture();

    void fill_sample(std::vector<float>& buf);

private:
    pa_simple* simple_{};
};
}  // namespace audio
