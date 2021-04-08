//
// Created by kira on 07.04.2021.
//

#include "pulse_adapter/pulse_exception.hpp"

#include <pulse/error.h>

namespace audio {
PulseException::PulseException(std::string error_string, int error_code)
    : err_str_{std::move(error_string) + "\npa_error: " + pa_strerror(error_code)} {}

const char* PulseException::what() const noexcept { return err_str_.c_str(); }
}  // namespace audio
