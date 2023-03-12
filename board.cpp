//
// Created by ethan on 2/22/2023.
//
#include "board.h"

board::board(){
    myBoard = new char*[ROWS];
    for(int i = 0; i<ROWS; i++){
        myBoard[i] = new char[COLS];
    }
}

board::board(const board& oldBoard){
    ROWS = oldBoard.ROWS;
    COLS = oldBoard.COLS;
    WIN_LENGTH = oldBoard.WIN_LENGTH;
    p1symbol = oldBoard.p1symbol;
    p2symbol = oldBoard.p2symbol;

    myBoard = new char*[ROWS];
    for(int i = 0; i<ROWS; i++){
        myBoard[i] = new char[COLS];
    }
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            myBoard[i][j] = oldBoard.myBoard[i][j];
        }
    }
    player1 = oldBoard.player1;
    player2 = oldBoard.player2;
    currentPlayer = oldBoard.currentPlayer;
    prevPlayer = oldBoard.prevPlayer;
}

board::board(int rows, int cols, int win_length, bool gameState){
    ROWS = rows;
    COLS = cols;
    WIN_LENGTH = win_length;
    myBoard = new char*[ROWS];
    for(int i = 0; i<ROWS; i++){
        myBoard[i] = new char[COLS];
    }
    player1 = new player(p1symbol, 1);
    if(gameState){
        player2 = new aiPlayer(p2symbol, 2);
    }
    else{
        player2 = new player(p2symbol, 2);
    }
    currentPlayer = player1;
    prevPlayer = player2;
}

void board::takeTurn(){
    printBoard();
    cout << "Player " << getCurrentPlayer()->getPlayerNum() << "'s Turn! ";
    //get a valid column choice
    currentPlayer->takeTurn(this->getRows(), this->getCols(), *this);
    placePiece(currentPlayer->getPlayerMove()[0],currentPlayer->getPlayerMove()[1],currentPlayer->getPiece());
}

void board::resetBoard(){
    for (int i = 0; i<ROWS; i++) {
        for (int j = 0; j<COLS; j++) {
            myBoard[i][j] = '_';
        }
    }
}

void board::printBoard(){
    for (int i = 0; i<ROWS; i++) {
        cout << '|';
        for (int j = 0; j<COLS; j++) {
            cout << myBoard[i][j] << '|';
        }
        cout << endl;
    }
    cout << endl;
}

bool board::checkColumn(int col){
    if(myBoard[0][col] == '_'){
        return true;
    }
    else{
        return false;
    }
}

int board::findRow(int col){
    for(int i = ROWS-1; i>-1; i--){
        if(myBoard[i][col] == '_'){
            return i;
        }
    }
    cout << "Column Checker not working properly" << endl;
    return -1;
}

void board::placePiece(int row, int col, char piece){
    myBoard[row][col] = piece;
    currentPlayer->getPlayerMove()[0] = row;
    currentPlayer->getPlayerMove()[1] = col;
}

bool board::checkwin(char piece){
    bool win = false;
    //check horizontal win conditions
    for (int i = 0; i < COLS - (WIN_LENGTH-1); i++) {

        for(int j = 0; j<WIN_LENGTH; j++){
            if(myBoard[prevPlayer->getPlayerMove()[0]][i+j] != piece){
                break;
            }
            else if(j == WIN_LENGTH-1){
                win = true;
            }
        }
    }
    //check vertical win conditions
    for (int i = 0; i < ROWS - (WIN_LENGTH-1); i++) {
        for(int j = 0; j<WIN_LENGTH; j++){
            if(myBoard[i+j][prevPlayer->getPlayerMove()[1]] != piece){
                break;
            }
            else if(j == WIN_LENGTH-1){
                win = true;
            }
        }
    }
    //check diagonal win conditions
    for (int i = 0; i < ROWS-(WIN_LENGTH-1); i++) {
        for (int j = 0; j < COLS - (WIN_LENGTH-1); j++) {
            for(int c = 0; c<WIN_LENGTH; c++){
                if(myBoard[i+c][j+c] != piece){
                    break;
                }
                else if(c == WIN_LENGTH-1){
                    win = true;
                }
            }
        }
    }
    for (int i = (WIN_LENGTH-1); i<ROWS; i++) {
        for (int j = 0; j < COLS-(WIN_LENGTH-1); j++) {
            for(int c = 0; c<WIN_LENGTH; c++){
                if(myBoard[i-c][j+c] != piece){
                    break;
                }
                else if(c == WIN_LENGTH-1){
                    win = true;
                }
            }
        }
    }

    return win;
}

bool board::checkTie(char** board) {
    bool over = true;
    for(int i = 0; i<COLS; i++) {
        if (board[0][i] == '_') {
            over = false;
        }
    }

    return over;
}


void board::turnSwitch() {
    if(currentPlayer == player1){
        currentPlayer = player2;
        prevPlayer = player1;
    }
    else{
        currentPlayer = player1;
        prevPlayer = player2;
    }
}

void board::declareWinner(){
    printBoard();
    cout << "Game Over!!! Player " << prevPlayer->getPlayerNum() << " is the WINNER!" << endl;
}


bool board::is_terminal_node(){
    if(checkwin(player1->getPiece()) || checkwin(player2->getPiece()) || checkTie(myBoard)){
        return true;
    }
    else{
        return false;
    }
}

vector<int> board::get_valid_locations(){
    vector<int> locations;
    for(int i = 0; i<COLS; i++){
        if(checkColumn(i)){
            locations.push_back(i);
        }
        else{
            locations.push_back(-1);
        }
    }
    return locations;
}

int board::random_available_column(vector<int> locations){
    int num;
    do {
        random_device rand;
        mt19937 mt(rand());
        uniform_int_distribution<mt19937::result_type> dist(0, 6);
        num = dist(mt);
    }while(std::find(locations.begin(), locations.end(),num) == locations.end());
    return num;
}

void board::setRows(int i){
    ROWS = i;
}

void board::setCols(int i){
    COLS = i;
}

void board::setWinLength(int i){
    WIN_LENGTH = i;
}

int board::getRows() const{
    return ROWS;
}

int board::getCols() const{
    return COLS;
}

char board::getPlayerPiece() {
    return p1symbol;
}

char board::getAiPiece() {
    return p2symbol;
}

int board::getWinLength() const{
    return WIN_LENGTH;
}
player* board::getCurrentPlayer() {
    return currentPlayer;
}

player* board::getPrevPlayer() {
    return prevPlayer;
}

char** board::getBoard(){
    return myBoard;
}

void board::setP1(char symbol) {
    p1symbol = symbol;
}

void board::setP2(char symbol) {
    p2symbol = symbol;
}

