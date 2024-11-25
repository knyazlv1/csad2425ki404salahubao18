#include "server.h"
#include <iostream>

int main() {
    while (true) {
        std::cout << "Enter game mode:\n";
        std::cout << "1. Man vs Man\n";
        std::cout << "2. Man vs AI (Random)\n";
        std::cout << "3. Man vs AI (Win Strategy)\n";
        std::cout << "4. AI (Random) vs AI (Win Strategy)\n";

        int mode;
        std::cin >> mode;

        std::string player1Move, player2Move, result;

        switch (mode) {
        case 1:
            std::cout << "Enter Player 1 move: ";
            std::cin >> player1Move;
            std::cout << "Enter Player 2 move: ";
            std::cin >> player2Move;
            result = playManVsMan(player1Move, player2Move);
            break;
        case 2:
            std::cout << "Enter Player 1 move: ";
            std::cin >> player1Move;
            result = playManVsAIRandom(player1Move);
            break;
        case 3:
            std::cout << "Enter Player 1 move: ";
            std::cin >> player1Move;
            result = playManVsAIStrategy(player1Move);
            break;
        case 4:
            result = playAIRandomVsAIStrategy();
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
            continue;
        }

        std::cout << "Result:\n" << result << "\n";
    }

    return 0;
}
