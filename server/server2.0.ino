/**
 * @file server2.0.ino
 * @brief Arduino server code for handling the "Rock, Paper, Scissors" game, including player vs player and AI game modes.
 */
#include <Arduino.h>

String lastPlayerMove = "";  ///< Stores the last move of the player for strategic AI calculations

/**
 * @brief Validates and returns a move string ("rock", "paper", or "scissors").
 * @param moveStr The input string representing a move.
 * @return A validated move string or "rock" as the default if input is invalid.
 */
String getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return "rock";
    if (moveStr == "paper") return "paper";
    if (moveStr == "scissors") return "scissors";
    return "rock";  
}

/**
 * @brief Determines the result of a "Rock, Paper, Scissors" game.
 * @param player1Move Move of Player 1.
 * @param player2Move Move of Player 2.
 * @return A string indicating the winner ("Player1 Wins", "Player2 Wins") or "Draw" if moves are equal.
 */
String determineWinner(String player1Move, String player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == "rock" && player2Move == "scissors") ||
        (player1Move == "scissors" && player2Move == "paper") ||
        (player1Move == "paper" && player2Move == "rock")) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}

/**
 * @brief Generates a random move for AI.
 * @return A string representing a random move ("rock", "paper", or "scissors").
 */
String getRandomMove() {
    int randomMove = random(0, 3);  
    if (randomMove == 0) return "rock";
    if (randomMove == 1) return "paper";
    return "scissors";
}

/**
 * @brief Generates a strategic move based on the opponent's last move.
 * @param opponentMove The last move of the opponent.
 * @return A move that wins against the opponent's last move.
 */
String getStrategicMove(String opponentMove) {
    if (opponentMove == "rock") return "paper";       
    if (opponentMove == "paper") return "scissors";   
    return "rock";                                   
}

/**
 * @brief Generates a move based on the AI strategy using the last player move.
 * @param currentPlayerMove The current move of the player.
 * @return The AI's strategic response to the player's move.
 * 
 * If it's the first round, the AI chooses a random move. For subsequent rounds, it
 * chooses a move that beats the player's last move.
 */
String getAIStrategyMove(String currentPlayerMove) {
    if (lastPlayerMove == "") {
        
        lastPlayerMove = currentPlayerMove;  
        return getRandomMove();  
    } else {
        
        String move = getStrategicMove(lastPlayerMove);
        lastPlayerMove = currentPlayerMove;  
        return move;
    }
}

/**
 * @brief Plays a "Man vs Man" game, determining the result.
 * @param player1Move Move of Player 1.
 * @param player2Move Move of Player 2.
 * @return A string representing the result of the game.
 */
String playManVsMan(String player1Move, String player2Move) {
    return determineWinner(player1Move, player2Move);
}

/**
 * @brief Plays a "Man vs AI (Random)" game, where AI randomly chooses a move.
 * @param player1Move The move of the human player.
 * @return A string containing the AI's move and the result of the game.
 */
String playManVsAIRandom(String player1Move) {
    String player2Move = getRandomMove();
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

/**
 * @brief Plays a "Man vs AI (Win Strategy)" game, where AI uses a strategy to counter the player's move.
 * @param player1Move The move of the human player.
 * @return A string containing the AI's move and the result of the game.
 */
String playManVsAIStrategy(String player1Move) {
    String player2Move = getAIStrategyMove(player1Move);  
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

/**
 * @brief Plays an "AI (Random) vs AI (Win Strategy)" game, where one AI plays randomly and the other strategically.
 * @return A string containing both AI moves and the result of the game.
 */
String playAIRandomVsAIStrategy() {
    String player1Move = getRandomMove();
    String player2Move = getAIStrategyMove(player1Move);
    return player1Move + "\n" + player2Move + "\n" + determineWinner(player1Move, player2Move);
}

/**
 * @brief Initializes serial communication for the game.
 */
void setup() {
    Serial.begin(9600);
    while (!Serial) {}
}

/**
 * @brief Main loop to listen for game mode and moves from the client and respond with the game result.
 * 
 * This loop reads the game mode and the moves from the client, plays the appropriate game mode, and sends the
 * result back to the client. The client is expected to send the mode followed by the player moves.
 */
void loop() {
    if (Serial.available()) {
        String mode = Serial.readStringUntil('\n');
        String player1MoveStr = Serial.readStringUntil('\n');

        String result;

        if (mode == "Man vs Man") {
            String player2MoveStr = Serial.readStringUntil('\n');
            result = playManVsMan(player1MoveStr, player2MoveStr);
            Serial.println(mode + "\n" + player1MoveStr + "\n" + player2MoveStr + "\n" + result);
        }
        else if (mode == "Man vs AI (Random)") {
            result = playManVsAIRandom(player1MoveStr);
            Serial.println(mode + "\n" + player1MoveStr + "\n" + result);
        }
        else if (mode == "Man vs AI (Win Strategy)") {
            result = playManVsAIStrategy(player1MoveStr);
            Serial.println(mode + "\n" + player1MoveStr + "\n" + result);
        }
        else if (mode == "AI (Random) vs AI (Win Strategy)") {
            result = playAIRandomVsAIStrategy();
            Serial.println(mode + "\n" + result);
        }
    }
}








