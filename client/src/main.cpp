
/**
 * @file main.cpp
 * @brief Main program to start the game and configure the serial port.
 */

#include <iostream>
#include "game.h"
#include "SerialPort.h"

 /**
  * @brief Main function that initializes the SerialPort and starts the game.
  *
  * @return int Returns 0 on success, 1 if the serial port configuration fails.
  */
int main() {
    SerialPort serialPort("COM3");
    if (!serialPort.configurePort()) {
        std::cerr << "Error: Unable to configure serial port." << std::endl;
        return 1;
    }

    playGame(serialPort);

    return 0;
}
