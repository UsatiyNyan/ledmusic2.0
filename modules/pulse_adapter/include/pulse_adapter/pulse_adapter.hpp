//
// Created by kira on 07.04.2021.
//

#pragma once

#include <pulse/pulseaudio.h>

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "pulse_device.hpp"
#include "pulse_mainloop.hpp"

namespace audio {
class PulseAdapter {
public:
    PulseAdapter();

    std::unordered_map<size_t, PulseDevice> get_sinks();
    std::unordered_map<size_t, PulseDevice> get_sources();

private:
    using PaMainloop = std::unique_ptr<pa_mainloop, std::function<void(pa_mainloop*)>>;
    using PulseContext = std::unique_ptr<pa_context, std::function<void(pa_context*)>>;

    PulseMainloop mainloop_{};
    PulseContext context_{pa_context_new(mainloop_.get_api(), "device_list"), pa_context_unref};
    bool ready_{};
};
}  // namespace audio
