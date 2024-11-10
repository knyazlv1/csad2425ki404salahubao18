#include <iostream>
#include "game.h"
#include "SerialPort.h"

int main() {
    SerialPort serialPort("COM3");
    if (!serialPort.configurePort()) {
        std::cerr << "Error: Unable to configure serial port." << std::endl;
        return 1;
    }

    playGame(serialPort);

    return 0;
}
