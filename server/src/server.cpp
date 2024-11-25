#include "server.h"
#include <cstdlib>

std::string lastPlayerMove = "";


std::string getMoveFromString(const std::string& moveStr) {
    if (moveStr == "rock") return "rock";
    if (moveStr == "paper") return "paper";
    if (moveStr == "scissors") return "scissors";
    return "rock";
}


std::string determineWinner(const std::string& player1Move, const std::string& player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == "rock" && player2Move == "scissors") ||
        (player1Move == "scissors" && player2Move == "paper") ||
        (player1Move == "paper" && player2Move == "rock")) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}


std::string getRandomMove() {
    int randomMove = std::rand() % 3;
    if (randomMove == 0) return "rock";
    if (randomMove == 1) return "paper";
    return "scissors";
}


std::string getStrategicMove(const std::string& opponentMove) {
    if (opponentMove == "rock") return "paper";
    if (opponentMove == "paper") return "scissors";
    return "rock";
}


std::string getAIStrategyMove(const std::string& currentPlayerMove) {
    if (lastPlayerMove.empty()) {
        lastPlayerMove = currentPlayerMove;
        return getRandomMove();
    }
    else {
        std::string move = getStrategicMove(lastPlayerMove);
        lastPlayerMove = currentPlayerMove;
        return move;
    }
}


std::string playManVsMan(const std::string& player1Move, const std::string& player2Move) {
    return determineWinner(player1Move, player2Move);
}

std::string playManVsAIRandom(const std::string& player1Move) {
    std::string player2Move = getRandomMove();
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

std::string playManVsAIStrategy(const std::string& player1Move) {
    std::string player2Move = getAIStrategyMove(player1Move);
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

std::string playAIRandomVsAIStrategy() {
    std::string player1Move = getRandomMove();
    std::string player2Move = getAIStrategyMove(player1Move);
    return player1Move + "\n" + player2Move + "\n" + determineWinner(player1Move, player2Move);
}
