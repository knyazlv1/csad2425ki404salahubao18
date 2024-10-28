#include <iostream>
#include "SerialPort.h"

// Main function initializes serial communication, sends a user-entered message to Arduino,
// and displays the response from Arduino.
int main() {
    SerialPort serialPort("\\\\.\\COM3");

    // Configure the serial port; if configuration fails, exit the program.
    if (!serialPort.configurePort()) {
        return 1;
    }

    // Prompt user for a message to send to Arduino.
    std::string message;
    std::cout << "Enter a message to send to Arduino: ";
    std::getline(std::cin, message);

    // Notify the user that the program is waiting for Arduino's response.
    std::cout << "Waiting for response from Arduino..." << std::endl;

    // Send the message and retrieve Arduino's response.
    std::string response = serialPort.sendMessage(message);

    // Display Arduino's response if available.
    if (!response.empty()) {
        std::cout << "Response from Arduino: " << response << std::endl;
    }

    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();  // window closing delay

    return 0;
}
