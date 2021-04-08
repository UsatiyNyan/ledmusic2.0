//
// Created by kira on 28.04.2020.
//
#include <iostream>
#include <numeric>

#include "pulse_adapter/pulse_adapter.hpp"
#include "pulse_adapter/pulse_capture.hpp"

int main() {
    audio::PulseAdapter pulse_adapter{};
    for (const auto& [index, device] : pulse_adapter.get_sources()) {
        std::cout << "=======[ Source PulseDevice #" << device.index << "]=======" << std::endl;
        std::cout << "Name: " << device.name << std::endl;
        std::cout << "Description: " << device.description << std::endl;
        std::cout << std::endl;
    }
    for (const auto& [index, device] : pulse_adapter.get_sinks()) {
        std::cout << "=======[ Sink PulseDevice #" << device.index << "]=======" << std::endl;
        std::cout << "Name: " << device.name << std::endl;
        std::cout << "Description: " << device.description << std::endl;
        std::cout << std::endl;
    }

    size_t source_index{};
    std::cin >> source_index;

    audio::PulseCapture pulse_capture(pulse_adapter.get_sources()[source_index]);
    std::vector<float> sample(1024);
    while (true) {
        pulse_capture.fill_sample(sample);
        std::cout << std::accumulate(sample.cbegin(), sample.cend(), 0.) << std::endl;
    }

    return 0;
}
