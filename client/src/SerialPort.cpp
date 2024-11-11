

/**
 * @file serialport.cpp
 * @brief Implements the SerialPort class for managing serial port communication.
 */
#include "serialport.h"
#include <iostream>

 /**
  * @brief Constructor for the SerialPort class. Attempts to open the specified serial port.
  *
  * @param portName The name of the port to open (e.g., "COM3").
  */
SerialPort::SerialPort(const std::string& portName) {
    serialHandle = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (serialHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Unable to open port: " << portName << std::endl;
    }
}

/**
 * @brief Destructor for the SerialPort class. Closes the port if it is open.
 */
SerialPort::~SerialPort() {
    if (serialHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(serialHandle);
    }
}

/**
 * @brief Configures the serial port by setting state and timeouts.
 *
 * @return true if the configuration succeeds; false otherwise.
 */
bool SerialPort::configurePort() {
    if (!setPortState()) {
        std::cerr << "Error: Unable to configure port state." << std::endl;
        return false;
    }
    if (!setPortTimeouts()) {
        std::cerr << "Error: Unable to set port timeouts." << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Sets the state of the serial port, such as baud rate and byte size.
 *
 * @return true if the port state is successfully set; false otherwise.
 */
bool SerialPort::setPortState() {
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(serialHandle, &dcbSerialParams)) {
        std::cerr << "Error: Unable to get port state." << std::endl;
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(serialHandle, &dcbSerialParams)) {
        std::cerr << "Error: Unable to configure port." << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Sets timeouts for the serial port to manage read and write operations.
 *
 * @return true if the timeouts are successfully set; false otherwise.
 */
bool SerialPort::setPortTimeouts() {
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(serialHandle, &timeouts)) {
        std::cerr << "Error: Unable to set timeouts." << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Sends a message through the serial port.
 *
 * @param message The message to send.
 * @return true if the message was sent successfully; false otherwise.
 */
bool SerialPort::sendMessage(const std::string& message) {
    DWORD bytesWritten;
    if (!WriteFile(serialHandle, message.c_str(), message.size(), &bytesWritten, NULL) || bytesWritten != message.size()) {
        std::cerr << "Error: Unable to send message." << std::endl;
        return false;
    }
    return true;
}

/**
 * @brief Receives a message from the serial port.
 *
 * @return std::string The received message.
 */
std::string SerialPort::receiveMessage() {
    char buffer[1024];
    DWORD bytesRead;
    if (!ReadFile(serialHandle, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        std::cerr << "Error: Unable to receive response." << std::endl;
        return "";
    }
    buffer[bytesRead] = '\0';
    return std::string(buffer);
}
