
/**
 * @file game.cpp
 * @brief Contains functions for managing and playing the game, including saving/loading game state, validating moves, and interacting with the SerialPort.
 */
#include "game.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

 /**
  * @brief Saves the current game state to a file.
  * @param filename The name of the file to save the game state.
  * @param mode The game mode (e.g., "Man vs Man", "Man vs AI").
  * @param player1Move The move of Player 1.
  * @param player2Move The move of Player 2.
  * @param player1Score The score of Player 1.
  * @param player2Score The score of Player 2.
  *
  * This function writes the game mode, players' moves, and their scores to a specified file, allowing the game to be resumed later.
  */
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

/**
 * @brief Loads a previously saved game state from a file.
 * @param filename The name of the file to load the game state from.
 * @param mode Reference to a string to store the loaded game mode.
 * @param player1Move Reference to a string to store the loaded move of Player 1.
 * @param player2Move Reference to a string to store the loaded move of Player 2.
 * @param player1Score Reference to an integer to store the loaded score of Player 1.
 * @param player2Score Reference to an integer to store the loaded score of Player 2.
 * @return True if the game state was loaded successfully; false otherwise.
 *
 * This function reads the game mode, players' moves, and scores from the specified file, restoring the game to a previous state.
 */
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

/**
 * @brief Manages the main game loop and handles player interactions and game modes.
 * @param serialPort A reference to the SerialPort object for sending and receiving messages to/from Arduino.
 *
 * The function provides options for starting a new game or continuing a previous one, allows players to choose a game mode, and handles player moves and game results.
 * It supports multiple game modes, including Man vs Man, Man vs AI, and AI vs AI, and saves game progress after each round.
 */
void playGame(SerialPort& serialPort) {
    std::string mode, player1Move, player2Move, result;
    int player1Score = 0, player2Score = 0;

    std::srand(static_cast<unsigned>(std::time(0)));

    bool loadedGame = false;  

    while (true) {
        
        std::cout << "\n===============================\n";
        std::cout << "          MAIN MENU\n";
        std::cout << "===============================\n";
        std::cout << "1. Continue previous game\n";
        std::cout << "2. Start a new game\n";
        std::cout << "Press 'e' to exit to the main menu, 'q' to quit the program.\n";
        std::cout << "===============================\n";
        std::cout << "Choose an option (1/2): ";

        char choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 'e') {
            return; 
        }
        else if (choice == 'q') {
            std::cout << "Exiting the program.\n";
            exit(0); 
        }

        if (choice == '1') {
            if (loadGameState("game.ini", mode, player1Move, player2Move, player1Score, player2Score)) {
                std::cout << "Previous game loaded.\n";
                loadedGame = true;  
            }
            else {
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

    
    if (!loadedGame) {
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

            if (modeChoice == 'e') {
                return; 
            }

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
    }
    else {
        std::cout << "Resuming in mode: " << mode << "\n";
    }

   
    while (true) {
        if (mode == "Man vs Man") {
            std::cout << "\nIt's time to play!\n";
            std::cout << "Player 1, enter your move (rock, paper, scissors) or 'e' to exit: ";
            std::getline(std::cin, player1Move);
            if (player1Move == "e") {
                std::cout << "Exiting game...\n";
                return; 
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
            std::cout << "\nPlayer 1, enter your move (rock, paper, scissors) or 'e' to exit: ";
            std::getline(std::cin, player1Move);
            if (player1Move == "e") {
                std::cout << "Exiting game...\n";
                return; 
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
            std::getline(std::cin, command);
            if (command != "start") {
                continue;
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




