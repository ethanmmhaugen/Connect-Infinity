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
    int ROWS = 6;
    int COLS = 7;
    int WIN_LENGTH = 4;
    char** myBoard;

    //Players info
    player* player1;
    player* player2;
    player* currentPlayer;
    player* prevPlayer;
    char p1symbol = '$';
    char p2symbol = '#';



public:
    board();
    board(const board& oldBoard);

    board(int rows, int cols, int win_length, bool gameState);

    void takeTurn();

    void resetBoard();

    void printBoard();

    bool checkColumn(int col);

    int findRow(int col);

    //regular connect 4 activites
    void placePiece(int row, int col, char piece);
    bool checkwin(char piece);
    bool checkTie(char** board);
    void turnSwitch();
    void declareWinner();

    //functions for minimax algo
    bool is_terminal_node();
    vector<int> get_valid_locations();
    int random_available_column(vector<int> locations);

    void setRows(int i);
    void setCols(int i);
    void setWinLength(int i);
    int getRows() const;
    int getCols() const;
    char getPlayerPiece();
    char getAiPiece();
    int getWinLength() const;
    player* getCurrentPlayer();
    player* getPrevPlayer();
    char** getBoard();
    void setP1(char symbol);
    void setP2(char symbol);

};

#endif //PA02_TEMPLATE_BOARD_H
