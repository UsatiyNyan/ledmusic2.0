//
// Created by kira on 09.04.2021.
//

#include "serial_port/serial_port.hpp"

namespace transport {
SerialPort::SerialPort(std::string port, uint32_t baud_rate) : serial_port_{io_service_, port} {
    serial_port_.set_option(boost::asio::serial_port_base::baud_rate{baud_rate});
}

void SerialPort::send_message(const google::protobuf::Message& message) {
    
}
}  // namespace transport
