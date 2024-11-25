#ifndef SERVER_H
#define SERVER_H

#include <string>

extern std::string lastPlayerMove;


std::string getMoveFromString(const std::string& moveStr);
std::string determineWinner(const std::string& player1Move, const std::string& player2Move);
std::string getRandomMove();
std::string getStrategicMove(const std::string& opponentMove);
std::string getAIStrategyMove(const std::string& currentPlayerMove);


std::string playManVsMan(const std::string& player1Move, const std::string& player2Move);
std::string playManVsAIRandom(const std::string& player1Move);
std::string playManVsAIStrategy(const std::string& player1Move);
std::string playAIRandomVsAIStrategy();

#endif // SERVER_H
#pragma once
