#ifndef GAME_H
#define GAME_H

#include <string>
#include "SerialPort.h"


void saveGameState(const std::string& filename, const std::string& mode, const std::string& player1Move, const std::string& player2Move, int player1Score, int player2Score);
bool loadGameState(const std::string& filename, std::string& mode, std::string& player1Move, std::string& player2Move, int& player1Score, int& player2Score);
bool validateMove(const std::string& move);
void playGame(SerialPort& serialPort);

#endif // GAME_H
#pragma once
