#include "serial_communication.h"
#include <iostream>
#include <string>
#include <fstream>

void logCommunication(const std::string& message, const std::string& response) {
    std::ofstream logFile("communication_log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "Sent message: " << message << "\n";
        logFile << "Received response: " << response << "\n";
        logFile << "---------------------------------\n";
        logFile.close();
    }
    else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}

int main() {
    boost::asio::serial_port* port = setupSerialPort("COM3", 9600);  // Налаштування порту
    if (!port) {
        std::cerr << "Failed to open serial port." << std::endl;
        return 1;
    }

    std::string message;
    std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    std::cout << "Waiting for response from Arduino..." << std::endl;
    // Відправка та отримання повідомлення
    std::string response;
    if (sendMessage(*port, message) && receiveResponse(*port, response)) {
        std::cout << "Response from Arduino: " << response << std::endl;
        logCommunication(message, response);  // Логування результату
    }
    else {
        std::cerr << "Communication error occurred." << std::endl;
    }

    port->close();
    delete port;
    return 0;
}
