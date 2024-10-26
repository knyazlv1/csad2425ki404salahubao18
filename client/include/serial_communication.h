#pragma once
#ifndef SERIAL_COMMUNICATION_H
#define SERIAL_COMMUNICATION_H

#include <boost/asio.hpp>
#include <string>

using namespace boost::asio;

// Функція для налаштування серійного порту
serial_port* setupSerialPort(const std::string& port_name, unsigned int baud_rate);

// Функція для надсилання повідомлення на Arduino
bool sendMessage(serial_port& port, const std::string& message);

// Функція для отримання відповіді від Arduino
bool receiveResponse(serial_port& port, std::string& response);

#endif
