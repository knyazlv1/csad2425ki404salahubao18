#pragma once
#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <windows.h>
#include <string>

class SerialPort {
public:
    SerialPort(const std::string& portName);
    ~SerialPort();

    bool configurePort();
    std::string sendMessage(const std::string& message);

private:
    HANDLE serialHandle;

    bool setPortState();
    bool setPortTimeouts();
};

#endif // SERIALPORT_H
