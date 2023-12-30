#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <vector>

class Board {
private:
    int size;
    std::vector<std::vector<char>> board;

public:
    Board(int size);
    void display();
    bool isFull();
    bool placeMove(int row, int col, char symbol);
    bool checkWin(char symbol);
};

#endif // BOARD_H_INCLUDED
