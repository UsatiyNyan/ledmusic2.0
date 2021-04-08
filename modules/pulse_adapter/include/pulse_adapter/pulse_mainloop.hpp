//
// Created by kira on 07.04.2021.
//

#pragma once

#include <pulse/pulseaudio.h>

#include <functional>
#include <memory>

#include "pulse_exception.hpp"

namespace audio {
class PulseMainloop {
public:
    PulseMainloop() = default;

    pa_mainloop_api* get_api() const;

    void iterate(bool block);

    int return_value() const;

private:
    std::unique_ptr<pa_mainloop, std::function<void(pa_mainloop*)>> mainloop_{pa_mainloop_new(),
                                                                              pa_mainloop_free};
    int return_value_{};
};
}  // namespace audio
