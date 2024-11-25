#include "pch.h"
#include <gtest/gtest.h>
#include "server.h"
#include <gtest/gtest.h>
#include <cstdlib>


TEST(ServerTest, GetMoveFromString_ValidMoves) {
    EXPECT_EQ(getMoveFromString("rock"), "rock");
    EXPECT_EQ(getMoveFromString("paper"), "paper");
    EXPECT_EQ(getMoveFromString("scissors"), "scissors");
}

TEST(ServerTest, GetMoveFromString_InvalidMove) {
    EXPECT_EQ(getMoveFromString("invalid"), "rock");
}


TEST(ServerTest, DetermineWinner_Draw) {
    EXPECT_EQ(determineWinner("rock", "rock"), "Draw");
    EXPECT_EQ(determineWinner("paper", "paper"), "Draw");
    EXPECT_EQ(determineWinner("scissors", "scissors"), "Draw");
}

TEST(ServerTest, DetermineWinner_Player1Wins) {
    EXPECT_EQ(determineWinner("rock", "scissors"), "Player1 Wins");
    EXPECT_EQ(determineWinner("paper", "rock"), "Player1 Wins");
    EXPECT_EQ(determineWinner("scissors", "paper"), "Player1 Wins");
}

TEST(ServerTest, DetermineWinner_Player2Wins) {
    EXPECT_EQ(determineWinner("rock", "paper"), "Player2 Wins");
    EXPECT_EQ(determineWinner("paper", "scissors"), "Player2 Wins");
    EXPECT_EQ(determineWinner("scissors", "rock"), "Player2 Wins");
}


TEST(ServerTest, GetRandomMove_ReturnsValidMove) {
    for (int i = 0; i < 100; ++i) {
        std::string move = getRandomMove();
        EXPECT_TRUE(move == "rock" || move == "paper" || move == "scissors");
    }
}


TEST(ServerTest, GetStrategicMove_CountersOpponent) {
    EXPECT_EQ(getStrategicMove("rock"), "paper");
    EXPECT_EQ(getStrategicMove("paper"), "scissors");
    EXPECT_EQ(getStrategicMove("scissors"), "rock");
}


TEST(ServerTest, GetAIStrategyMove_FirstRoundRandom) {
    lastPlayerMove = "";
    std::string move = getAIStrategyMove("rock");
    EXPECT_TRUE(move == "rock" || move == "paper" || move == "scissors");
    EXPECT_EQ(lastPlayerMove, "rock");
}

TEST(ServerTest, GetAIStrategyMove_SubsequentRoundsStrategic) {
    lastPlayerMove = "rock";
    EXPECT_EQ(getAIStrategyMove("paper"), "paper");
    EXPECT_EQ(lastPlayerMove, "paper");
}


TEST(ServerTest, PlayManVsMan_ResultCorrect) {
    EXPECT_EQ(playManVsMan("rock", "scissors"), "Player1 Wins");
    EXPECT_EQ(playManVsMan("rock", "rock"), "Draw");
    EXPECT_EQ(playManVsMan("scissors", "rock"), "Player2 Wins");
}


TEST(ServerTest, PlayManVsAIRandom_ResultContainsAI) {
    std::string result = playManVsAIRandom("rock");
    std::size_t pos = result.find("\n");
    ASSERT_NE(pos, std::string::npos);
    std::string aiMove = result.substr(0, pos);
    EXPECT_TRUE(aiMove == "rock" || aiMove == "paper" || aiMove == "scissors");
}


TEST(ServerTest, PlayManVsAIStrategy_ResultContainsAI) {
    lastPlayerMove = "";
    std::string result = playManVsAIStrategy("rock");
    std::size_t pos = result.find("\n");
    ASSERT_NE(pos, std::string::npos);
    std::string aiMove = result.substr(0, pos);
    EXPECT_TRUE(aiMove == "rock" || aiMove == "paper" || aiMove == "scissors");
}


TEST(ServerTest, PlayAIRandomVsAIStrategy_ValidResult) {
    std::string result = playAIRandomVsAIStrategy();
    std::size_t firstPos = result.find("\n");
    ASSERT_NE(firstPos, std::string::npos);

    std::string ai1Move = result.substr(0, firstPos);
    EXPECT_TRUE(ai1Move == "rock" || ai1Move == "paper" || ai1Move == "scissors");

    std::size_t secondPos = result.find("\n", firstPos + 1);
    ASSERT_NE(secondPos, std::string::npos);

    std::string ai2Move = result.substr(firstPos + 1, secondPos - firstPos - 1);
    EXPECT_TRUE(ai2Move == "rock" || ai2Move == "paper" || ai2Move == "scissors");

    std::string outcome = result.substr(secondPos + 1);
    EXPECT_TRUE(outcome == "Player1 Wins" || outcome == "Player2 Wins" || outcome == "Draw");
}
