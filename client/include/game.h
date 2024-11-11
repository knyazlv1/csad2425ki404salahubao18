
/**
 * @file game.h
 * @brief Declares functions for managing and playing the game.
 */
#ifndef GAME_H
#define GAME_H

#include <string>
#include "SerialPort.h"

 /**
  * @brief Saves the current game state to a file.
  *
  * @param filename The name of the file to save to.
  * @param mode The game mode.
  * @param player1Move Move of player 1.
  * @param player2Move Move of player 2.
  * @param player1Score Score of player 1.
  * @param player2Score Score of player 2.
  */
void saveGameState(const std::string& filename, const std::string& mode, const std::string& player1Move, const std::string& player2Move, int player1Score, int player2Score);

/**
 * @brief Loads the game state from a file.
 *
 * @param filename The name of the file to load from.
 * @param mode Reference to game mode.
 * @param player1Move Reference to move of player 1.
 * @param player2Move Reference to move of player 2.
 * @param player1Score Reference to score of player 1.
 * @param player2Score Reference to score of player 2.
 * @return true if loading was successful; false otherwise.
 */
bool loadGameState(const std::string& filename, std::string& mode, std::string& player1Move, std::string& player2Move, int& player1Score, int& player2Score);

/**
 * @brief Validates if the given move is valid (e.g., rock, paper, scissors).
 *
 * @param move The move to validate.
 * @return true if the move is valid; false otherwise.
 */
bool validateMove(const std::string& move);

/**
 * @brief Manages the game logic and communicates with the Arduino.
 *
 * @param serialPort Reference to SerialPort for communication.
 */
void playGame(SerialPort& serialPort);

#endif // GAME_H
#pragma once
