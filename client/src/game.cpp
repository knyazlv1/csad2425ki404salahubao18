#include "game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>


void saveGameState(const std::string& filename, const std::string& mode, const std::string& player1Move, const std::string& player2Move, int player1Score, int player2Score) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << mode << std::endl;
        outFile << player1Move << std::endl;
        outFile << player2Move << std::endl;
        outFile << player1Score << std::endl;
        outFile << player2Score << std::endl;
    }
    else {
        std::cerr << "Error: Unable to open file for saving game state." << std::endl;
    }
}

bool loadGameState(const std::string& filename, std::string& mode, std::string& player1Move, std::string& player2Move, int& player1Score, int& player2Score) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::getline(inFile, mode);
        std::getline(inFile, player1Move);
        std::getline(inFile, player2Move);
        inFile >> player1Score;
        inFile >> player2Score;
        inFile.ignore();
        return true;
    }
    else {
        std::cerr << "Error: Unable to open file for loading game state." << std::endl;
        return false;
    }
}

void playGame(SerialPort& serialPort) {
    std::string mode, player1Move, player2Move, result;
    int player1Score = 0, player2Score = 0;

    std::srand(static_cast<unsigned>(std::time(0)));

    while (true) {
       
        std::cout << "\n===============================\n";
        std::cout << "          MAIN MENU\n";
        std::cout << "===============================\n";
        std::cout << "1. Continue previous game\n";
        std::cout << "2. Start a new game\n";
        std::cout << "Press 'q' to quit the program.\n";
        std::cout << "===============================\n";
        std::cout << "Choose an option (1/2): ";

        char choice;
        std::cin >> choice;
        std::cin.ignore();

        
        if (choice == 'q') {
            std::cout << "Exiting the program.\n";
            exit(0); 
        }

        if (choice == '1') {
            if (!loadGameState("game.ini", mode, player1Move, player2Move, player1Score, player2Score)) {
                std::cout << "No previous game found, starting a new game.\n";
            }
            break;
        }
        else if (choice == '2') {
            break;
        }
        else {
            std::cout << "Invalid choice, please try again.\n";
            continue; 
        }
    }

    while (true) {  
        std::cout << "\n===============================\n";
        std::cout << "          SELECT GAME MODE\n";
        std::cout << "===============================\n";
        std::cout << "1. Man vs Man\n";
        std::cout << "2. Man vs AI (Random)\n";
        std::cout << "3. Man vs AI (Win Strategy)\n";
        std::cout << "4. AI (Random) vs AI (Win Strategy)\n";
        std::cout << "Press 'e' to exit to the main menu.\n";
        std::cout << "===============================\n";
        std::cout << "Choose an option (1-4 or 'e' to exit): ";

        char modeChoice;
        std::cin >> modeChoice;
        std::cin.ignore();

        

        switch (modeChoice) {
        case '1': mode = "Man vs Man"; break;
        case '2': mode = "Man vs AI (Random)"; break;
        case '3': mode = "Man vs AI (Win Strategy)"; break;
        case '4': mode = "AI (Random) vs AI (Win Strategy)"; break;
        default:
            std::cout << "Invalid option, please choose a valid game mode.\n";
            continue; 
        }

        break; 
    }

    while (true) {  
        if (mode == "Man vs Man") {
            std::cout << "\nIt's time to play!\n";
            std::cout << "Player 1, enter your move (rock, paper, scissors) or 'q' to exit: ";
            std::getline(std::cin, player1Move);
            if (player1Move == "q") {
                std::cout << "Exiting game...\n";
                return; // Вихід з гри
            }
            for (int i = 0; i < 45; i++) {
                std::cout << "*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n";
            }
            std::cout << "Player 2, enter your move: ";
            std::getline(std::cin, player2Move);
            serialPort.sendMessage(mode + "\n" + player1Move + "\n" + player2Move);

            std::string response = serialPort.receiveMessage();
            size_t pos1 = response.find('\n');
            size_t pos2 = response.find('\n', pos1 + 1);
            size_t pos3 = response.find('\n', pos2 + 1);

            mode = response.substr(0, pos1);
            player1Move = response.substr(pos1 + 1, pos2 - pos1 - 1);
            player2Move = response.substr(pos2 + 1, pos3 - pos2 - 1);
            result = response.substr(pos3 + 1);
        }
        else if (mode == "Man vs AI (Random)" || mode == "Man vs AI (Win Strategy)") {
            std::cout << "\nPlayer 1, enter your move (rock, paper, scissors) or 'q' to exit: ";
            std::getline(std::cin, player1Move);
            if (player1Move == "q") {
                std::cout << "Exiting game...\n";
                return; // Вихід з гри
            }

            serialPort.sendMessage(mode + "\n" + player1Move);

            std::string response = serialPort.receiveMessage();
            size_t pos1 = response.find('\n');
            size_t pos2 = response.find('\n', pos1 + 1);
            size_t pos3 = response.find('\n', pos2 + 1);

            mode = response.substr(0, pos1);
            player1Move = response.substr(pos1 + 1, pos2 - pos1 - 1);
            player2Move = response.substr(pos2 + 1, pos3 - pos2 - 1);
            result = response.substr(pos3 + 1);
        }
        else if (mode == "AI (Random) vs AI (Win Strategy)") {
            std::cout << "\nAI vs AI battle! Type 'start' to begin the round.\n";
            std::string command;
            std::cout << "Please write - s - to start round or press q to exit:";
            std::getline(std::cin, command);
            if (command == "s") {
                continue;
            }
            else if (command == "q") {
                std::cout << "Exiting game...\n";
                return; 
            }
            serialPort.sendMessage(mode + "\n");

            std::string response = serialPort.receiveMessage();

            size_t pos1 = response.find('\n');
            size_t pos2 = response.find('\n', pos1 + 1);
            size_t pos3 = response.find('\n', pos2 + 1);

            mode = response.substr(0, pos1);
            player1Move = response.substr(pos1 + 1, pos2 - pos1 - 1);
            player2Move = response.substr(pos2 + 1, pos3 - pos2 - 1);
            result = response.substr(pos3 + 1);
        }

        if (result.find("Player1 Wins") != std::string::npos) player1Score++;
        if (result.find("Player2 Wins") != std::string::npos) player2Score++;

        std::cout << "\nGame Update:\n";
        std::cout << "Mode: " << mode << "\n";
        std::cout << "Player 1 Move: " << player1Move << ", Player 2 Move: " << player2Move << "\n";
        std::cout << "Result: " << result << "\n";
        std::cout << "Current Score - Player 1: " << player1Score << " | Player 2: " << player2Score << "\n";

        saveGameState("game.ini", mode, player1Move, player2Move, player1Score, player2Score);
    }
}



