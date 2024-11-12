
/**
 * @file serialport.h
 * @brief Declares the SerialPort class for managing serial port communication.
 */
#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

 /**
  * @class SerialPort
  * @brief Manages serial port operations, including configuration and message sending/receiving.
  */
class SerialPort {
public:

    /**
     * @brief Constructs a SerialPort object and attempts to open the specified port.
     *
     * @param portName The name of the port (e.g., "COM3").
     */
    SerialPort(const std::string& portName);

    /**
     * @brief Destructor that closes the port if it is open.
     */
    ~SerialPort();

    /**
     * @brief Configures the port by setting state and timeouts.
     *
     * @return true if the port is successfully configured; false otherwise.
     */
    bool configurePort();

    /**
     * @brief Sends a message through the serial port.
     *
     * @param message The message to send.
     * @return true if the message is successfully sent; false otherwise.
     */
    bool sendMessage(const std::string& message);

    /**
     * @brief Receives a message from the serial port.
     *
     * @return std::string The received message.
     */
    std::string receiveMessage();

private:
    HANDLE serialHandle; ///< Handle to the serial port.

    /**
     * @brief Sets the state of the port (baud rate, byte size, etc.).
     *
     * @return true if the state is successfully set; false otherwise.
     */
    bool setPortState();

    /**
     * @brief Sets timeouts for read and write operations.
     *
     * @return true if timeouts are successfully set; false otherwise.
     */
    bool setPortTimeouts();
};

#endif // SERIAL_H
