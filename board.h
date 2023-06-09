//
// Created by ethan on 1/15/2023.
//

#ifndef PA02_TEMPLATE_BOARD_H
#define PA02_TEMPLATE_BOARD_H


#include <chrono>
#include <thread>
#include <algorithm>
#include "player.h"

using namespace std;

class board{

private:
    //board info
    int ROWS;
    int COLS;
    int WIN_LENGTH;
    char** myBoard;

    //Players info
    player* player1;
    player* player2;
    player* currentPlayer;
    player* prevPlayer;




public:
    board();
    board(const board& oldBoard);
    ~board();
    board(int rows, int cols, int win_length, bool gameState, char p1symbol, char p2symbol, int aiDifficulty);

    //regular connect 4 activites
    void takeTurn();
    void resetBoard();
    void printBoard();
    bool checkColumn(int col);
    int findRow(int col);
    void placePiece(int row, int col, char piece);
    void clearPiece(int row, int col);
    bool checkwin(char piece);
    bool checkTie();
    void turnSwitch();
    void declareWinner();
    void declareTie();

    //functions for minimax algo
    bool is_terminal_node();
    vector<int> get_valid_locations();
    static int random_available_column(vector<int> locations);

    //useful getters and setters
    int getRows() const;
    int getCols() const;
    char getPlayerPiece();
    int getWinLength() const;
    player* getCurrentPlayer();
    player* getPrevPlayer();
    char** getBoard();

};

#endif //PA02_TEMPLATE_BOARD_H
