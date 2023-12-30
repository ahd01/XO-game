#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>
#include "Board.h"
#include "Player.h"

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player* currentPlayer;
    bool isGameOver;

public:
    Game(const std::string& player1Name, const std::string& player2Name, int boardSize);
    void start();
    void playerTurn();
    bool isDraw();
};

#endif // GAME_H_INCLUDED
