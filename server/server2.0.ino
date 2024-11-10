/*#include <Arduino.h>

enum Move { ROCK, PAPER, SCISSORS };

Move getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return ROCK;
    if (moveStr == "paper") return PAPER;
    if (moveStr == "scissors") return SCISSORS;
    return ROCK;  // За замовчуванням
}

String determineWinner(Move player1Move, Move player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == ROCK && player2Move == SCISSORS) ||
        (player1Move == SCISSORS && player2Move == PAPER) ||
        (player1Move == PAPER && player2Move == ROCK)) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
}

void loop() {
    if (Serial.available()) {
        String mode = Serial.readStringUntil('\n');
        String player1MoveStr = Serial.readStringUntil('\n');
        String player2MoveStr = Serial.readStringUntil('\n');

        Move player1Move = getMoveFromString(player1MoveStr);
        Move player2Move = getMoveFromString(player2MoveStr);

        String result = determineWinner(player1Move, player2Move);

        // Відправляємо результат гри назад клієнту
        Serial.println(result);
    }
}*/
/*#include <Arduino.h>

enum Move { ROCK, PAPER, SCISSORS };

Move getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return ROCK;
    if (moveStr == "paper") return PAPER;
    if (moveStr == "scissors") return SCISSORS;
    return ROCK;  // За замовчуванням
}

String determineWinner(Move player1Move, Move player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == ROCK && player2Move == SCISSORS) ||
        (player1Move == SCISSORS && player2Move == PAPER) ||
        (player1Move == PAPER && player2Move == ROCK)) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}

void setup() {
    Serial.begin(9600);
    while (!Serial) {}
}

void loop() {
    if (Serial.available()) {
        String mode = Serial.readStringUntil('\n');
        String player1MoveStr = Serial.readStringUntil('\n');
        String player2MoveStr = Serial.readStringUntil('\n');

        Move player1Move = getMoveFromString(player1MoveStr);
        Move player2Move = getMoveFromString(player2MoveStr);

        String result = determineWinner(player1Move, player2Move);

        // Відправляємо на клієнт: режим гри, вибір гравців, результат
        Serial.println(mode + "\n" + player1MoveStr + "\n" + player2MoveStr + "\n" + result);
    }
}*/
/*#include <Arduino.h>

// Функція для перетворення рядка в хід
String getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return "rock";
    if (moveStr == "paper") return "paper";
    if (moveStr == "scissors") return "scissors";
    return "rock";  // За замовчуванням
}

// Визначення переможця між двома ходами
String determineWinner(String player1Move, String player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == "rock" && player2Move == "scissors") ||
        (player1Move == "scissors" && player2Move == "paper") ||
        (player1Move == "paper" && player2Move == "rock")) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}

// Випадковий хід AI
String getRandomMove() {
    int randomMove = random(0, 3);  // Випадковий хід (0 - rock, 1 - paper, 2 - scissors)
    if (randomMove == 0) return "rock";
    if (randomMove == 1) return "paper";
    return "scissors";
}

// Стратегічний хід AI (перемагати залежно від ходу опонента)
String getStrategicMove(String opponentMove) {
    if (opponentMove == "rock") return "paper";       // Виграти проти rock
    if (opponentMove == "paper") return "scissors";   // Виграти проти paper
    return "rock";                                   // Виграти проти scissors
}

// Функція для гри Man vs Man
String playManVsMan(String player1Move, String player2Move) {
    return determineWinner(player1Move, player2Move);
}

// Функція для гри Man vs AI (Random)
String playManVsAIRandom(String player1Move) {
    String player2Move = getRandomMove();
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

// Функція для гри Man vs AI (Win Strategy)
String playManVsAIStrategy(String player1Move) {
    String player2Move = getStrategicMove(player1Move);
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

// Функція для гри AI (Random) vs AI (Win Strategy)
String playAIRandomVsAIStrategy() {
    String player1Move = getRandomMove();
    String player2Move = getStrategicMove(player1Move);
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
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
            Serial.println(mode + "\n" + player1MoveStr + "\n" + result);
        }
    }
}*/
#include <Arduino.h>

String lastPlayerMove = "";  // Змінна для зберігання попереднього ходу гравця

// Функція для перетворення рядка в хід
String getMoveFromString(const String& moveStr) {
    if (moveStr == "rock") return "rock";
    if (moveStr == "paper") return "paper";
    if (moveStr == "scissors") return "scissors";
    return "rock";  // За замовчуванням
}

// Визначення переможця між двома ходами
String determineWinner(String player1Move, String player2Move) {
    if (player1Move == player2Move) return "Draw";
    if ((player1Move == "rock" && player2Move == "scissors") ||
        (player1Move == "scissors" && player2Move == "paper") ||
        (player1Move == "paper" && player2Move == "rock")) {
        return "Player1 Wins";
    }
    return "Player2 Wins";
}

// Випадковий хід AI
String getRandomMove() {
    int randomMove = random(0, 3);  // Випадковий хід (0 - rock, 1 - paper, 2 - scissors)
    if (randomMove == 0) return "rock";
    if (randomMove == 1) return "paper";
    return "scissors";
}

// Стратегічний хід AI (перемагати залежно від попереднього ходу гравця)
String getStrategicMove(String opponentMove) {
    if (opponentMove == "rock") return "paper";       // Виграти проти rock
    if (opponentMove == "paper") return "scissors";   // Виграти проти paper
    return "rock";                                   // Виграти проти scissors
}

// Оновлений AI, що пам'ятає попередній хід гравця
String getAIStrategyMove(String currentPlayerMove) {
    if (lastPlayerMove == "") {
        // Якщо попереднього ходу нема, AI вибирає випадково
        lastPlayerMove = currentPlayerMove;  // Зберігаємо поточний хід як останній
        return getRandomMove();  // Випадковий хід
    } else {
        // Якщо попередній хід є, AI вибирає стратегічний хід
        String move = getStrategicMove(lastPlayerMove);
        lastPlayerMove = currentPlayerMove;  // Оновлюємо останній хід
        return move;
    }
}

// Функція для гри Man vs Man
String playManVsMan(String player1Move, String player2Move) {
    return determineWinner(player1Move, player2Move);
}

// Функція для гри Man vs AI (Random)
String playManVsAIRandom(String player1Move) {
    String player2Move = getRandomMove();
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

// Функція для гри Man vs AI (Win Strategy)
String playManVsAIStrategy(String player1Move) {
    String player2Move = getAIStrategyMove(player1Move);  // Використовуємо нову логіку
    return player2Move + "\n" + determineWinner(player1Move, player2Move);
}

// Функція для гри AI (Random) vs AI (Win Strategy)
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








