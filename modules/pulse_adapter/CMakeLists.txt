## pulseaudio lib
find_path(PULSEAUDIO_INCLUDE_DIR NAMES pulse/pulseaudio.h)
find_library(PULSEAUDIO_LIBRARY NAMES pulse)

add_library(pulse_adapter STATIC
        src/pulse_exception.cpp
        src/pulse_mainloop.cpp
        src/pulse_adapter.cpp
        src/pulse_capture.cpp)
target_include_directories(pulse_adapter PUBLIC include)
target_link_libraries(pulse_adapter PUBLIC pulse-simple pulse)

add_executable(device_list_example example/device_list_example.cpp)
target_link_libraries(device_list_example pulse_adapter)
