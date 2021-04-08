//
// Created by kira on 28.04.2020.
//

#pragma once

#include <exception>
#include <string>

namespace audio {
class BassException : public std::exception {
public:
    explicit BassException(std::string error_string);
    const char* what() const noexcept override;

private:
    std::string err_str_;
};
}  // namespace audio
