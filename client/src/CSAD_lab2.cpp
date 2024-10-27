#include <iostream>
#include "SerialPort.h"

int main() {
    SerialPort serialPort(L"\\\\.\\COM3");

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

    return 0;
}
