cmake_minimum_required(VERSION 3.15)
project(ledmusic
        VERSION 2.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty)

add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        $<$<COMPILE_LANGUAGE:CXX>:-Wsuggest-override>
        -Wshadow
        -Wfloat-equal
        -Wcast-qual
        -Wlogical-op
        -Werror
        -Wcast-align
)

add_subdirectory(modules)
add_subdirectory(example)

add_executable(${PROJECT_NAME} src/main.cpp)

if (BUILD_TESTING)
    add_subdirectory(test)
endif (BUILD_TESTING)
