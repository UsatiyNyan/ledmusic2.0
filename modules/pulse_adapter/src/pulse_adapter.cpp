//
// Created by kira on 07.04.2021.
//

#include "pulse_adapter/pulse_adapter.hpp"

#include <algorithm>

#include "pulse_adapter/pulse_exception.hpp"

namespace audio {
using ReadyAndDevices = std::pair<bool, std::unordered_map<size_t, PulseDevice>>;
using OperationUniquePtr = std::unique_ptr<pa_operation, std::function<void(pa_operation*)>>;

PulseAdapter::PulseAdapter() {
    // This function connects to the pulse server
    if (pa_context_connect(context_.get(), nullptr, PA_CONTEXT_NOFLAGS, nullptr) < 0) {
        throw PulseException{"pa_context_connect", 0};
    }

    pa_context_set_state_callback(
        context_.get(),
        [](pa_context* ctx, void* userdata) {
            bool& pa_ready = *static_cast<bool*>(userdata);
            auto state = pa_context_get_state(ctx);
            switch (state) {
                case pa_context_state::PA_CONTEXT_FAILED:
                case pa_context_state::PA_CONTEXT_TERMINATED:
                    throw PulseException{"pa_state failed or terminated", 0};
                case pa_context_state::PA_CONTEXT_READY:
                    pa_ready = true;
                    break;
                default:
                    break;
            }
        },
        &ready_);
    // We can't do anything until PA is ready, so just iterate the mainloop
    while (!ready_) {
        mainloop_.iterate(true);
    }
}

std::unordered_map<size_t, PulseDevice> PulseAdapter::get_sinks() {
    ReadyAndDevices ready_and_devices{};
    auto operation = OperationUniquePtr{
        pa_context_get_sink_info_list(
            context_.get(),
            [](pa_context*, const pa_sink_info* sink_info, int eol, void* userdata) {
                auto& [ready, devices] = *static_cast<ReadyAndDevices*>(userdata);

                if (eol > 0 or !sink_info) {
                    ready = true;
                    return;
                }

                PulseDevice device{sink_info->index, sink_info->name, sink_info->description};

                if (devices.find(device.index) != devices.end()) {
                    ready = true;
                    return;
                }

                devices.emplace(device.index, std::move(device));
            },
            &ready_and_devices),
        pa_operation_unref};
    while (!ready_and_devices.first) {
        mainloop_.iterate(true);
    }
    return std::move(ready_and_devices.second);
}

std::unordered_map<size_t, PulseDevice> PulseAdapter::get_sources() {
    ReadyAndDevices ready_and_devices{};
    auto operation = OperationUniquePtr{
        pa_context_get_source_info_list(
            context_.get(),
            [](pa_context*, const pa_source_info* source_info, int eol, void* userdata) {
                auto& [ready, devices] = *static_cast<ReadyAndDevices*>(userdata);

                if (eol > 0 or !source_info) {
                    ready = true;
                    return;
                }

                PulseDevice device{source_info->index, source_info->name, source_info->description};

                if (devices.find(device.index) != devices.end()) {
                    ready = true;
                    return;
                }

                devices.emplace(device.index, std::move(device));
            },
            &ready_and_devices),
        pa_operation_unref};
    while (!ready_and_devices.first) {
        mainloop_.iterate(true);
    }
    return std::move(ready_and_devices.second);
}
}  // namespace audio
