#include <iostream>
#include <string>
#include <vector>
#include <random>

using namespace std;

class Player {
private:
    string name;
    char symbol;
public:
    Player(const string& playerName, char playerSymbol);
    string getName() const;
    char getSymbol() const;
};

Player::Player(const string& playerName, char playerSymbol) : name(playerName), symbol(playerSymbol) {}

string Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}

class Board {
protected:
    int size;
    vector<vector<char>> board;
public:
    Board(int size);
    virtual void display() = 0;
    virtual bool isFull() = 0;
    virtual bool placeMove(int row, int col, char symbol) = 0;
    virtual bool checkWin(char symbol) = 0;
    virtual int getSize() const = 0;
    virtual vector<vector<char>>& getBoard() = 0;
};

Board::Board(int n) : size(n), board(n, vector<char>(n, ' ')) {}

class TicTacToeBoard : public Board {
public:
    TicTacToeBoard(int size) : Board(size) {}
    void display() override;
    bool isFull() override;
    bool placeMove(int row, int col, char symbol) override;
    bool checkWin(char symbol) override;
    int getSize() const override {
        return size;
    }
    vector<vector<char>>& getBoard() override {
        return board;
    }
};

void TicTacToeBoard::display() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << board[i][j];
            if (j < size - 1)
                cout << " |";
        }
        cout << '\n';
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                cout << "------";
            }
            cout << '\n';
        }
    }
}

bool TicTacToeBoard::isFull() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool TicTacToeBoard::placeMove(int row, int col, char symbol) {
    if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != ' ')
        return false;
    board[row][col] = symbol;
    return true;
}

bool TicTacToeBoard::checkWin(char symbol) {
    for (int i = 0; i < size; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol)
                rowWin = false;
            if (board[j][i] != symbol)
                colWin = false;
        }
        if (rowWin || colWin)
            return true;
    }

    bool mainDiagWin = true;
    bool antiDiagWin = true;
    for (int j = 0; j < size; j++) {
        if (board[j][j] != symbol)
            mainDiagWin = false;
        if (board[j][size - j - 1] != symbol)
            antiDiagWin = false;
    }
    if (mainDiagWin || antiDiagWin)
        return true;
    return false;
}

class RandomPlayer {
public:
    void makeMove(Board& board, char symbol, int& row, int& col);
};

class GameManager {
private:
    Board* board;
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    bool isGameOver;

public:
    GameManager(const string& player1Name, const string& player2Name, int boardSize);
    ~GameManager();
    void start();
    void playerTurn();
    bool isDraw();
};

GameManager::GameManager(const string& player1Name, const string& player2Name, int boardSize) : isGameOver(false) {
    board = new TicTacToeBoard(boardSize);
    player1 = new Player(player1Name, 'X');
    player2 = new Player(player2Name, 'O');
    currentPlayer = player1;
}

GameManager::~GameManager() {
    delete board;
    delete player1;
    delete player2;
}

void GameManager::start() {
    cout << "WELCOME TO THE GAME, TIC TAC TOE\n";
    board->display();
    while (!isGameOver) {
        playerTurn();
        board->display();
        if (board->checkWin(currentPlayer->getSymbol())) {
            cout << currentPlayer->getName() << " WINS\n";
            isGameOver = true;
        }
        else if (board->isFull()) {
            cout << "DRAW\n";
            isGameOver = true;
        }
        else {
            if (currentPlayer == player1)
                currentPlayer = player2;
            else
                currentPlayer = player1;
        }
    }
}

void GameManager::playerTurn() {
    int row, col;
    if (currentPlayer == player1) {
        cout << player1->getName() << "'s turn (X): ";
        cin >> row >> col;
    }
    else {
        RandomPlayer randomPlayer;
        cout << player2->getName() << "'s turn (O): ";
        randomPlayer.makeMove(*board, player2->getSymbol(), row, col);
        cout << row << " " << col << endl;
    }
    while (!board->placeMove(row, col, currentPlayer->getSymbol())) {
        cout << "Invalid move. Try again: ";
        cin >> row >> col;
    }
}

bool GameManager::isDraw() {
    return board->isFull() && !board->checkWin(player1->getSymbol()) && !board->checkWin(player2->getSymbol());
}

void RandomPlayer::makeMove(Board& board, char symbol, int& row, int& col) {
    vector<pair<int, int>> availableMoves;
    int size = board.getSize();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board.getBoard()[i][j] == ' ') {
                availableMoves.push_back(make_pair(i, j));
            }
        }
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, availableMoves.size() - 1);

    pair<int, int> randomMove = availableMoves[dis(gen)];
    row = randomMove.first;
    col = randomMove.second;
}

int main() {
    int choice;
    cout<<"enter 1 for  Four-in-a-row and 2 for Pyramic Tic-Tac-Toe";
    cin>>choice;
    if(choice == 1)
    {
        string player1Name, player2Name;
        int boardSize;
        cout << "Enter name for Player 1 (X): ";
        cin >> player1Name;
        cout << "Enter name for Player 2 (O): ";
        cin >> player2Name;
        cout << "Enter board size: ";
        cin >> boardSize;
        GameManager game(player1Name, player2Name, boardSize);
        game.start();
    }
}

/*#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Board {
public:
    Board(int size) : size(size) {
        board.resize(size, vector<char>(size, ' '));
    }
    virtual ~Board() = default;
    virtual void display() = 0;
    virtual bool isFull() = 0;
    virtual bool placeMove(int row, int col, char symbol) = 0;
    virtual bool checkWin(char symbol) = 0;
    virtual int getSize() const = 0;
    virtual vector<vector<char>>& getBoard() = 0;

protected:
    int size;
    vector<vector<char>> board;
};

class TicTacToeBoard : public Board {
public:
    TicTacToeBoard(int size) : Board(size) {}
    void display() override;
    bool isFull() override;
    bool placeMove(int row, int col, char symbol) override;
    bool checkWin(char symbol) override;
    int getSize() const override {
        return size;
    }
    vector<vector<char>>& getBoard() override {
        return board;
    }
};

void TicTacToeBoard::display() {
    int boardSize = getSize();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            cout << board[i][j];
            if (j != boardSize - 1)
                cout << " | ";
        }
        cout << endl;
        if (i != boardSize - 1) {
            for (int k = 0; k < boardSize - 1; ++k)
                cout << "----";
            cout << "---" << endl;
        }
    }
}

bool TicTacToeBoard::isFull() {
    int boardSize = getSize();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool TicTacToeBoard::placeMove(int row, int col, char symbol) {
    if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ') {
        board[row][col] = symbol;
        return true;
    }
    return false;
}

bool TicTacToeBoard::checkWin(char symbol) {
    int boardSize = getSize();

    // Check rows
    for (int i = 0; i < boardSize; ++i) {
        bool win = true;
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win)
            return true;
    }

    // Check columns
    for (int j = 0; j < boardSize; ++j) {
        bool win = true;
        for (int i = 0; i < boardSize; ++i) {
            if (board[i][j] != symbol) {
                win = false;
                break;
            }
        }
        if (win)
            return true;
    }

    // Check diagonals
    bool win = true;
    for (int i = 0; i < boardSize; ++i) {
        if (board[i][i] != symbol) {
            win = false;
            break;
        }
    }
    if (win)
        return true;

    win = true;
    for (int i = 0; i < boardSize; ++i) {
        if (board[i][boardSize - i - 1] != symbol) {
            win = false;
            break;
        }
    }
    return win;
}

class Player {
public:
    virtual ~Player() = default;
    virtual void makeMove(Board& board, char symbol, int& row, int& col) = 0;
    virtual char getSymbol() const = 0;
    virtual string getName() const = 0;
};

class HumanPlayer : public Player {
public:
    void makeMove(Board& board, char symbol, int& row, int& col) override;
    char getSymbol() const override {
        return 'X';
    }
    string getName() const override {
        return "Human Player";
    }
};

void HumanPlayer::makeMove(Board& board, char symbol, int& row, int& col) {
    int boardSize = board.getSize();

    while (true) {
        cout << "Enter row and column (0-" << boardSize - 1 << "): ";
        cin >> row >> col;
        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize && board.placeMove(row, col, symbol))
            break;
        cout << "Invalid move. Try again." << endl;
    }
}

class RandomPlayer : public Player {
public:
    void makeMove(Board& board, char symbol, int& row, int& col) override;

    char getSymbol() const override {
        return 'O';
    }
    string getName() const override {
        return "Random Player";
    }

private:
    bool makeRandomMove(Board& board, char symbol, int& row, int& col);
    bool isWinningMove(Board& board, char symbol, int row, int col);
};

void RandomPlayer::makeMove(Board& board, char symbol, int& row, int& col) {
    if (!makeRandomMove(board, symbol, row, col)) {
        // No random move available, perform a random move using backtracking
        int boardSize = board.getSize();
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                if (board.placeMove(i, j, symbol) && isWinningMove(board, symbol, i, j)) {
                    row = i;
                    col = j;
                    return;
                }
                board.placeMove(i, j, ' ');  // Undo the move
            }
        }
    }
}

bool RandomPlayer::makeRandomMove(Board& board, char symbol, int& row, int& col) {
    vector<pair<int, int>> availableMoves;
    int boardSize = board.getSize();
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board.getBoard()[i][j] == ' ') {
                availableMoves.push_back(make_pair(i, j));
            }
        }
    }

    if (availableMoves.empty()) {
        return false;  // No moves available
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, availableMoves.size() - 1);

    pair<int, int> randomMove = availableMoves[dis(gen)];
    row = randomMove.first;
    col = randomMove.second;
    return true;
}

bool RandomPlayer::isWinningMove(Board& board, char symbol, int row, int col) {
    board.placeMove(row, col, symbol);
    bool isWinning = board.checkWin(symbol);
    board.placeMove(row, col, ' ');  // Undo the move
    return isWinning;
}

int main() {
    int boardSize;
    cout << "Enter the size of the Tic-Tac-Toe board: ";
    cin >> boardSize;

    Board* board = new TicTacToeBoard(boardSize);
    Player* player1 = new HumanPlayer();
    Player* player2 = new RandomPlayer();

    Player* currentPlayer = player1;
    int row, col;
    bool isGameOver = false;

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "Player 1: " << player1->getName() << " (X)" << endl;
    cout << "Player 2: " << player2->getName() << " (O)" << endl;
    cout << endl;

    while (!isGameOver) {
        board->display();
        cout << endl;

        if (currentPlayer == player1) {
            cout << currentPlayer->getName() << " (X) makes a move." << endl;
            currentPlayer->makeMove(*board, currentPlayer->getSymbol(), row, col);
        } else {
            cout << currentPlayer->getName() << " (O) makes a move." << endl;
            currentPlayer->makeMove(*board, currentPlayer->getSymbol(), row, col);
        }

        cout << endl;

        if (board->checkWin(currentPlayer->getSymbol())) {
            board->display();
            cout << endl;
            cout << currentPlayer->getName() << " wins!" << endl;
            isGameOver = true;
        } else if (board->isFull()) {
            board->display();
            cout << endl;
            cout << "It's a draw!" << endl;
            isGameOver = true;
        } else {
            if (currentPlayer == player1)
                currentPlayer = player2;
            else
                currentPlayer = player1;
        }
    }

    delete board;
    delete player1;
    delete player2;

    return 0;
}*/
