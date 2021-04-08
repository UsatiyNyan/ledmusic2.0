//
// Created by kira on 07.04.2021.
//

#pragma once

#include <exception>
#include <string>

namespace audio {
class PulseException : public std::exception {
public:
    explicit PulseException(std::string error_string, int error_code);
    const char* what() const noexcept override;

private:
    std::string err_str_;
};
}  // namespace audio
