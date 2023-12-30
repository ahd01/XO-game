#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>

class Player {
private:
    std::string name;
    char symbol;

public:
    Player(const std::string& playerName, char playerSymbol);
    std::string getName() const;
    char getSymbol() const;
};

#endif // PLAYER_H_INCLUDED
