add_library(bass_adapter STATIC
        src/bass_adapter.cpp
        src/bass_exception.cpp)
target_include_directories(bass_adapter PUBLIC
        include)
target_link_libraries(bass_adapter PUBLIC
        bass
        pulse_adapter)

add_executable(bass_sample_data_example example/bass_sample_data_example.cpp)
target_link_libraries(bass_sample_data_example bass_adapter)
