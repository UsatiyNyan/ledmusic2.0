//
// Created by kira on 28.04.2020.
//
#include <iostream>
#include <numeric>

#include "bass_adapter/bass_adapter.hpp"
#include "pulse_adapter/pulse_adapter.hpp"

int main() {
    audio::PulseAdapter pulse_adapter{};
    size_t source_index{};
    std::cin >> source_index;

    audio::BassAdapter bass_adapter{pulse_adapter.get_sources()[source_index]};

    std::vector<float> sample_buffer{};
    sample_buffer.assign(2048, 0);
    while (true) {
        bass_adapter.process_sample(sample_buffer);
        std::cout << std::accumulate(sample_buffer.cbegin(), sample_buffer.cend(), 0.F)
                  << std::endl;
    }
    return 0;
}