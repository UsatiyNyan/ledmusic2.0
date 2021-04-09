find_package(Boost COMPONENTS system REQUIRED)

include(cmake/transport.cmake)

transport_generate_protos(TARGET serial_port_messages
        INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pb)

add_library(serial_port STATIC
        src/serial_port.cpp)
target_include_directories(serial_port PUBLIC
        include)
target_link_libraries(serial_port PUBLIC
        Boost::system
        serial_port_messages)

#add_executable(serial_port_example example/serial_port_example.cpp)
#target_link_libraries(serial_port_example serial_port)
