#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

class SerialPort {
public:
    SerialPort(const std::string& portName);
    ~SerialPort();

    bool configurePort();
    bool sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    HANDLE serialHandle;

    bool setPortState();
    bool setPortTimeouts();
};

#endif // SERIAL_H
