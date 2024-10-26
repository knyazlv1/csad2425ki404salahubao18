#include "serial_communication.h"
#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

serial_port* setupSerialPort(const std::string& port_name, unsigned int baud_rate) {
    try {
        io_service* io = new io_service;
        serial_port* port = new serial_port(*io, port_name);
        port->set_option(serial_port_base::baud_rate(baud_rate));
        port->set_option(serial_port_base::character_size(8));
        port->set_option(serial_port_base::parity(serial_port_base::parity::none));
        port->set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
        port->set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
        return port;
    }
    catch (boost::system::system_error& e) {
        std::cerr << "Error opening serial port: " << e.what() << std::endl;
        return nullptr;
    }
}

bool sendMessage(serial_port& port, const std::string& message) {
    try {
        std::string msg = message + '\n';
        write(port, buffer(msg));
        return true;
    }
    catch (boost::system::system_error& e) {
        std::cerr << "Error sending message: " << e.what() << std::endl;
        return false;
    }
}

bool receiveResponse(serial_port& port, std::string& response) {
    try {
        char c;
        response.clear();
        while (true) {
            read(port, buffer(&c, 1));
            if (c == '\n') break;
            response += c;
        }
        return true;
    }
    catch (boost::system::system_error& e) {
        std::cerr << "Error receiving response: " << e.what() << std::endl;
        return false;
    }
}
