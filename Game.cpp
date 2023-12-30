#include "Game.h"
#include <iostream>

Game::Game(const std::string& player1Name, const std::string& player2Name, int boardSize)
    : player1(player1Name, 'X'), player2(player2Name, 'O'), board(boardSize), currentPlayer(&player1), isGameOver(false)
{
}

void Game::start()
{
    cout << "WELCOME TO THE GAME, TIC TAC TOE\n";
    board.display();
    while (!isGameOver)
    {
        playerTurn();
        board.display();
        if (board.checkWin(currentPlayer->getSymbol()))
        {
            cout << currentPlayer->getName() << " WINS\n";
            isGameOver = true;
        }
        else if (board.isFull())
        {
            cout << "It's a draw game\n";
            isGameOver = true;
        }
        else
        {
            currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }
    }
}
