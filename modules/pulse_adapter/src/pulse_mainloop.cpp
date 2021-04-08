//
// Created by kira on 07.04.2021.
//

#include "pulse_adapter/pulse_mainloop.hpp"

namespace audio {
pa_mainloop_api* PulseMainloop::get_api() const { return pa_mainloop_get_api(mainloop_.get()); }

void PulseMainloop::iterate(bool block) {
    if (pa_mainloop_iterate(mainloop_.get(), block, &return_value_) < 0) {
        throw PulseException{
            "pa_mainloop_iterate with return_value of " + std::to_string(return_value_), 0};
    }
}

int PulseMainloop::return_value() const { return return_value_; }
}  // namespace audio
