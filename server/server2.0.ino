
#include <Arduino.h>

String lastPlayerMove = "";  


String getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return "rock";
    if (moveStr == "paper") return "paper";
    if (moveStr == "scissors") return "scissors";
    return "rock";  
}


String determineWinner(String player1Move, String player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == "rock" && player2Move == "scissors") ||
        (player1Move == "scissors" && player2Move == "paper") ||
        (player1Move == "paper" && player2Move == "rock")) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}


String getRandomMove() {
    int randomMove = random(0, 3);  
    if (randomMove == 0) return "rock";
    if (randomMove == 1) return "paper";
    return "scissors";
}


String getStrategicMove(String opponentMove) {
    if (opponentMove == "rock") return "paper";       
    if (opponentMove == "paper") return "scissors";   
    return "rock";                                   
}


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


String playManVsMan(String player1Move, String player2Move) {
    return determineWinner(player1Move, player2Move);
}


String playManVsAIRandom(String player1Move) {
    String player2Move = getRandomMove();
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}


String playManVsAIStrategy(String player1Move) {
    String player2Move = getAIStrategyMove(player1Move);  
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}


String playAIRandomVsAIStrategy() {
    String player1Move = getRandomMove();
    String player2Move = getAIStrategyMove(player1Move);
    return player1Move + "\n" + player2Move + "\n" + determineWinner(player1Move, player2Move);
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
}

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








