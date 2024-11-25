#include "pch.h"
#include <gtest/gtest.h>

#include <gtest/gtest.h>
#include "game.h"
#include <fstream>
#include <cstdio>

#include <string>
#include <sstream>


TEST(GameTests, SaveGameState) {
  
    std::string filename = "test_game.ini";
    std::string mode = "Man vs Man";
    std::string player1Move = "rock";
    std::string player2Move = "scissors";
    int player1Score = 1;
    int player2Score = 0;

    
    saveGameState(filename, mode, player1Move, player2Move, player1Score, player2Score);

    
    std::ifstream inFile(filename);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    ASSERT_EQ(line, mode);

    std::getline(inFile, line);
    ASSERT_EQ(line, player1Move);

    std::getline(inFile, line);
    ASSERT_EQ(line, player2Move);

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), player1Score);

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), player2Score);

    inFile.close();
    std::remove(filename.c_str());  
}


TEST(GameTests, LoadGameState) {
    
    std::string filename = "test_game.ini";
    std::ofstream outFile(filename);
    outFile << "Man vs Man\n";
    outFile << "rock\n";
    outFile << "scissors\n";
    outFile << 1 << "\n";
    outFile << 0 << "\n";
    outFile.close();

    std::string mode, player1Move, player2Move;
    int player1Score, player2Score;

    
    bool result = loadGameState(filename, mode, player1Move, player2Move, player1Score, player2Score);

    
    ASSERT_TRUE(result);
    ASSERT_EQ(mode, "Man vs Man");
    ASSERT_EQ(player1Move, "rock");
    ASSERT_EQ(player2Move, "scissors");
    ASSERT_EQ(player1Score, 1);
    ASSERT_EQ(player2Score, 0);

    std::remove(filename.c_str());  
}

void playGame(std::string mode, std::string playerMove1, std::string playerMove2, int& player1Score, int& player2Score) {
    if (mode == "Man vs Man") {
        if (playerMove1 == "rock" && playerMove2 == "scissors") {
            player1Score++;
        }
        else if (playerMove1 == "scissors" && playerMove2 == "paper") {
            player1Score++;
        }
        else if (playerMove1 == "paper" && playerMove2 == "rock") {
            player1Score++;
        }
        else if (playerMove1 == playerMove2) {
          
        }
        else {
            player2Score++;
        }
    }
    else if (mode == "Man vs AI (Random)") {
        if (playerMove1 == "rock" && playerMove2 == "scissors") {
            player1Score++;
        }
        else if (playerMove1 == "scissors" && playerMove2 == "paper") {
            player1Score++;
        }
        else if (playerMove1 == "paper" && playerMove2 == "rock") {
            player1Score++;
        }
        else if (playerMove1 == playerMove2) {
            // Нічия
        }
        else {
            player2Score++;
        }
    }

    
    std::ofstream outFile("game.ini");
    outFile << mode << "\n" << playerMove1 << "\n" << playerMove2 << "\n";
    outFile << player1Score << "\n" << player2Score << "\n";
    outFile.close();
}



TEST(GameTests, PlayGame_ManVsMan) {
    std::string mode = "Man vs Man";
    std::string player1Move = "rock";
    std::string player2Move = "scissors";
    int player1Score = 0, player2Score = 0;

    
    playGame(mode, player1Move, player2Move, player1Score, player2Score);

    
    std::ifstream inFile("game.ini");
    std::string line;

   
    std::getline(inFile, line);
    ASSERT_EQ(line, mode);

    std::getline(inFile, line);
    ASSERT_EQ(line, player1Move);

    std::getline(inFile, line);
    ASSERT_EQ(line, player2Move);

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), 1);  

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), 0);  

    inFile.close();
    std::remove("game.ini");  
}


TEST(GameTests, PlayGame_ManVsAI) {
    std::string mode = "Man vs AI (Random)";
    std::string playerMove1 = "rock";     
    std::string playerMove2 = "paper";    
    int player1Score = 0, player2Score = 0;

    
    playGame(mode, playerMove1, playerMove2, player1Score, player2Score);

    
    std::ifstream inFile("game.ini");
    std::string line;

    
    std::getline(inFile, line);
    ASSERT_EQ(line, mode); 

    std::getline(inFile, line);
    ASSERT_EQ(line, playerMove1);  

    std::getline(inFile, line);
    ASSERT_EQ(line, playerMove2);  

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), 0);  

    std::getline(inFile, line);
    ASSERT_EQ(std::stoi(line), 1);  

    inFile.close();
    std::remove("game.ini");  
}


TEST(GameTests, PlayGame_Exit) {
    std::string mode = "Exit";
    int playerScore = 0, aiScore = 0;

    
    playGame(mode, "", "", playerScore, aiScore);

    
    std::ifstream inFile("game.ini");
    std::string line;
    std::getline(inFile, line);
    ASSERT_EQ(line, mode);  

    inFile.close();
    std::remove("game.ini");  
}

std::string mockGetUserChoice() {
    return "Rock";
}

void mockSendMessage(const char* message) {
    EXPECT_STREQ(message, "Rock");
}

std::string mockReceiveMessagePlayer1Wins() {
    return "Player1:Rock;Player2:Scissors;Result:Player 1 wins";
}

std::string mockReceiveMessagePlayer2Wins() {
    return "Player1:Rock;Player2:Paper;Result:Player 2 wins";
}

std::string mockReceiveMessageDraw() {
    return "Player1:Rock;Player2:Rock;Result:Draw";
}

std::string mockReceiveMessageInvalid() {
    return "Invalid Response Format";
}