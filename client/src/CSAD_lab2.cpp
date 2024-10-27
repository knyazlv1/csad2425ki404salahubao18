#include <iostream>
#include "SerialPort.h"

int main() {
    SerialPort serialPort("\\\\.\\COM3");

    if (!serialPort.configurePort()) {
        return 1;
    }

    std::string message;
    std::cout << "Enter a message to send to Arduino: ";
    std::getline(std::cin, message);

    std::cout << "Waiting for response from Arduino..." << std::endl;
    std::string response = serialPort.sendMessage(message);

    if (!response.empty()) {
        std::cout << "Response from Arduino: " << response << std::endl;
    }
    std::cout << "Press Enter to continue..." << std::endl;
    std::cin.get();  // Затримує програму до натискання Enter
    return 0;

    return 0;
}
