//
// Created by kira on 09.04.2021.
//

#pragma once

#include <boost/asio.hpp>
#include <google/protobuf/message.h>

namespace transport {
class SerialPort {
public:
    SerialPort(std::string port, uint32_t baud_rate);

    void send_message(const google::protobuf::Message &message);

private:
    boost::asio::io_service io_service_{};
    boost::asio::serial_port serial_port_;
};
}  // namespace transport
