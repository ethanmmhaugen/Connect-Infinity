//
// Created by ethan on 12/27/2022.
//

#ifndef PA02_TEMPLATE_CONNECT_4_H
#define PA02_TEMPLATE_CONNECT_4_H

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>


using namespace std;
using namespace chrono;
using namespace this_thread;
class connect_4 {



private:
    int COLS = 7;
    int ROWS = 6;
    int WIN_LENGTH = 4;
    char playerPiece;
    char aiPiece;
    bool gameOver = false;
    int playerMove[2];
    bool aiGame;
    bool aiTurn;
    int aiDifficulty;

public:
//creates the empty board
    connect_4(){
        playerPiece = '$';
        aiPiece = '#';
        aiGame = true;
        aiTurn = false;
        aiDifficulty = 2;
    }
    
    /*void reset(){
        initializeBoard();
    }
    */
    void initializeBoard(char** board) {
        for (int i = 0; i<ROWS; i++) {
            for (int j = 0; j<COLS; j++) {
                board[i][j] = '_';
            }
        }
    }

//Prints the board array with the lines and such
    void printBoard(char** board) {
        for (int i = 0; i<ROWS; i++) {
            for (int j = 0; j<COLS; j++) {

                cout << "|" << board[i][j];
            }
            cout << '|' << endl;
        }
        cout << endl;
    }

//Lets 2 players pick characters one after another. Repeat characters aren't allowed
    void pickSymbols() {
        cout << "Enter Player 1's Character:\n";
        cin >> playerPiece;
        do {
            cout << "Enter Player 2's Character:\n";
            cin >> aiPiece;
            if (playerPiece == aiPiece) {
                cout << "Nice try breaking my game. Please pick a different character for Player 2...\n";
            }
        } while (playerPiece == aiPiece);

    }

    void swapOrder(){
        if(aiTurn){
            aiTurn = false;
        }
        else{
            aiTurn = true;
        }
    }

//switches which players turn it is
    void turnSwitch() {
        if(aiTurn){
            aiTurn = false;
        }
        else{
            aiTurn = true;
        }
    }

//checks if a column has empty spots left
    bool colCheck(int move, char** board) {
        bool spacecounter = false;
        for (int i = 0; i < ROWS; i++) {
            if (board[i][move] == '_') {
                spacecounter = true;
            }
        }
        if (spacecounter) {
            return true;
        }
        return false;
    }

//Lets user pick a column and sends it to column checker before returning the confirmed valid column
    void colChoice(char** board) {
        int move;
        bool isValid;
        do {
            cout << "Choose a column 1-" << COLS << ":\n";
            cin >> move;
            move -= 1;
            if (move > (COLS-1) || move < 0) {
                cout << "Invalid Choice.";
                continue;
            }
            isValid = colCheck(move, board);
        } while (move > (COLS-1) || move < 0 || !isValid);
        playerMove[1] = move;
    }
    void colChoice(int i){
        playerMove[1] = i;
    }

//sends the confirmed column to the board array in the lowest available row
    void takeTurn(char** turnBoard, char piece, int rows) {
        for (int i = rows-1; i > -1; i--) {
            if (turnBoard[i][playerMove[1]] == '_') {
                turnBoard[i][playerMove[1]] = piece;
                playerMove[0] = i;
                break;
            }
        }
    }

//declares the winner and allows the turn loop to break
    void playerWin(char** board) {
        printBoard(board);
        if(aiTurn) {
            cout << "Game Over!! Player 2 Wins!\n";
        }
        else{
            cout << "Game Over!! Player 1 Wins!\n";
        }
        gameOver = true;
    }

//checks all win conditions and calls playerWin if there is a win
    bool checkWin(char** board, char piece) {
        bool win = false;
        //check horizontal win conditions
        for (int i = 0; i < COLS - (WIN_LENGTH-1); i++) {

            for(int j = 0; j<WIN_LENGTH; j++){
                if(board[playerMove[0]][i+j] != piece){
                    break;
                }
                else if(j == WIN_LENGTH-1){
                    win = true;
                }
            }
            /*if (board[playerMove[0]][i] == piece && board[playerMove[0]][i] == board[playerMove[0]][i + 1]
                && board[playerMove[0]][i] == board[playerMove[0]][i + 2]
                && board[playerMove[0]][i] == board[playerMove[0]][i + 3]) {
                win = true;
            }
            */
        }
        //check vertical win conditions
        for (int i = 0; i < ROWS - (WIN_LENGTH-1); i++) {
            for(int j = 0; j<WIN_LENGTH; j++){
                if(board[i+j][playerMove[1]] != piece){
                    break;
                }
                else if(j == WIN_LENGTH-1){
                    win = true;
                }
            }
            /*
            if (board[i][playerMove[1]] == piece && board[i][playerMove[1]] == board[i + 1][playerMove[1]] && board[i][playerMove[1]] == board[i + 2][playerMove[1]] &&
                board[i][playerMove[1]] == board[i + 3][playerMove[1]]) {
                win = true;
            }
            */
        }
        //check diagonal win conditions
        for (int i = 0; i < ROWS-(WIN_LENGTH-1); i++) {
            for (int j = 0; j < COLS - (WIN_LENGTH-1); j++) {
                for(int c = 0; c<WIN_LENGTH; c++){
                    if(board[i+c][j+c] != piece){
                        break;
                    }
                    else if(c == WIN_LENGTH-1){
                        win = true;
                    }
                }
                /*if (board[i][j] == piece && board[i][j] == board[i + 1][j + 1] &&
                    board[i][j] == board[i + 2][j + 2] &&
                    board[i][j] == board[i + 3][j + 3]) {
                    win = true;
                }
                */
            }
        }
        for (int i = (WIN_LENGTH-1); i<ROWS; i++) {
            for (int j = 0; j < COLS-(WIN_LENGTH-1); j++) {
                for(int c = 0; c<WIN_LENGTH; c++){
                    if(board[i-c][j+c] != piece){
                        break;
                    }
                    else if(c == WIN_LENGTH-1){
                        win = true;
                    }
                }
                /*
                if (board[i][j] == piece && board[i][j] == board[i - 1][j + 1] &&
                    board[i][j] == board[i - 2][j + 2] &&
                    board[i][j] == board[i - 3][j + 3]) {
                    win = true;
                }
                */
            }
        }

        return win;
    }

//Prints tie game and breaks the game loop
    void tieGame(char** board) {
        printBoard(board);
        cout << "Game Over!! Tie!!\n";
    }

//checks for tie and calls tieGame if its tied
    bool checkTie(char** board) {
        bool over = true;
        for(int i = 0; i<COLS; i++) {
            if (board[0][i] == '_') {
                over = false;
            }
        }

        return over;
    }

    void aiTakeTurn(int difficulty, char** board){
        //Random column selection
        if(difficulty == 0){
            random_device rand;
            mt19937 mt(rand());
            uniform_int_distribution<mt19937::result_type> dist(0,(COLS-1));
            colChoice(dist(mt));
        }


        //This is medium difficulty bot
        // colChoice(pick_best_move(board, aiPiece, playerPiece));
        else {
            vector<int> result = minimax(board, difficulty, -1000000, 1000000, true);
            colChoice(result[3]);
        }
        //Time delay before taking turn
        //sleep_for(seconds(2));

        //Take the turn
        takeTurn(board, aiPiece, ROWS);
    }

    int scorePosition(char piece, char opponents_piece, char** scoringBoard){
        int score = 0;
        //Score horizontals
        for(int i = 0; i<ROWS; i++){
            //array of individual rows
            char row_array[COLS];
            for(int j = 0; j<COLS; j++){
                row_array[j] = scoringBoard[i][j];
            }
            //Window of 4 pieces at a time that we look at for score,
            // iterate through and count the pieces
            for(int c = 0; c<COLS-(WIN_LENGTH-1); c++){
                //Here we check each window
                int pieceCount = 0;
                int spaceCount = 0;
                int opponentCount = 0;
                for(int p = c; p<c+WIN_LENGTH; p++){
                    if(row_array[p] == piece){
                        pieceCount++;
                    }
                    else if(row_array[p] == opponents_piece){
                        opponentCount++;
                    }
                    else{
                        spaceCount++;
                    }

                }

                //now check scores in that window
                if(pieceCount == WIN_LENGTH){
                    score+=100;
                }
                else if(opponentCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score-=200;
                }
                else if(pieceCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score+=5;
                }
                else if(pieceCount == (WIN_LENGTH-2) && spaceCount == 2){
                    score+=2;
                }
            }
        }

        //vertical score checking
        for(int i = 0; i<COLS; i++){
            //array of individual rows
            char col_array[ROWS];
            for(int j = 0; j<ROWS; j++){
                col_array[j] = scoringBoard[j][i];
            }
            //Window of 4 pieces at a time that we look at for score,
            // iterate through and count the pieces
            for(int c = 0; c<ROWS-(WIN_LENGTH-1); c++){
                //Here we check each window
                int pieceCount = 0;
                int spaceCount = 0;
                int opponentCount = 0;
                for(int p = c; p<c+WIN_LENGTH; p++){
                    if(col_array[p] == piece){
                        pieceCount++;
                    }
                    else if(col_array[p] == opponents_piece){
                        opponentCount++;
                    }
                    else{
                        spaceCount++;
                    }

                }

                //now check scores in that window

                //now check scores in that window
                if(pieceCount == WIN_LENGTH){
                    score+=100;
                }
                else if(opponentCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score-=200;
                }
                else if(pieceCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score+=5;
                }
                else if(pieceCount == (WIN_LENGTH-2) && spaceCount == 2){
                    score+=2;
                }
            }
        }

        //score negative slope diagonals
        for(int i = 0; i<ROWS-(WIN_LENGTH-1); i++){
            for(int j = 0; j<COLS-(WIN_LENGTH-1); j++){
                int pieceCount = 0;
                int spaceCount = 0;
                int opponentCount = 0;
                for(int c = 0; c<WIN_LENGTH; c++) {
                    char spot = scoringBoard[i+c][j+c];
                    if(spot == piece){
                        pieceCount++;
                    }
                    else if(spot == opponents_piece){
                        opponentCount++;
                    }
                    else{
                        spaceCount++;
                    }
                }
                //now check scores in that window

                //now check scores in that window
                if(pieceCount == WIN_LENGTH){
                    score+=100;
                }
                else if(opponentCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score-=200;
                }
                else if(pieceCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score+=5;
                }
                else if(pieceCount == (WIN_LENGTH-2) && spaceCount == 2){
                    score+=2;
                }
            }
        }

        //score positive slope diagonals
        for(int i = (WIN_LENGTH-1); i<ROWS; i++){
            for(int j = 0; j<COLS-(WIN_LENGTH-1); j++){
                int pieceCount = 0;
                int spaceCount = 0;
                int opponentCount = 0;
                for(int c = 0; c<WIN_LENGTH; c++) {
                    char spot = scoringBoard[i-c][j+c];
                    if(spot == piece){
                        pieceCount++;
                    }
                    else if(spot == opponents_piece){
                        opponentCount++;
                    }
                    else{
                        spaceCount++;
                    }

                }
                //now check scores in that window

                //now check scores in that window
                if(pieceCount == WIN_LENGTH){
                    score+=100;
                }
                else if(opponentCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score-=200;
                }
                else if(pieceCount == (WIN_LENGTH-1) && spaceCount == 1){
                    score+=5;
                }
                else if(pieceCount == (WIN_LENGTH-2) && spaceCount == 2){
                    score+=2;
                }
            }
        }
        return score;
    }

    vector<int> get_valid_locations(char** myBoard){
        vector<int> locations;
        for(int i = 0; i<COLS; i++){
            if(colCheck(i, myBoard)){
                locations.push_back(i);
            }
            else{
                locations.push_back(-1);
            }
        }
        return locations;
    }
    //looks 1 turn ahead.... not bad

    int pick_best_move(char** myBoard, char myPiece, char opponentPiece){
        vector<int> locations = get_valid_locations(myBoard);
        int bestScore = -10000;
        int bestColumn = random_available_column(locations);
        for(int i = 0; i<locations.size(); i++) {
            if(locations[i] == -1){
                continue;
            }
            char **tmpBoard;
            for(int j = 0; j<ROWS; j++){
                for(int k = 0; k<COLS; k++){
                    tmpBoard[j][k] = myBoard[j][k];
                }
            }
            colChoice(i);
            takeTurn(tmpBoard, myPiece, ROWS);
            int score = scorePosition(myPiece, opponentPiece, tmpBoard);
            if(i == (WIN_LENGTH/2)){
                score +=2;
            }
            if(score>bestScore){
                bestScore = score;
                bestColumn = i;
            }
            cout << "Column: " << i << " has score of " << score << endl;
        }
        return bestColumn;
    }

    bool is_terminal_node(char** terminalBoard){
        if(checkWin(terminalBoard, playerPiece) || checkWin(terminalBoard, aiPiece) || checkTie(terminalBoard)){
            return true;
        }
        else{
            return false;
        }

    }
    static int random_available_column(vector<int> locations){
        int num;
        do {
            random_device rand;
            mt19937 mt(rand());
            uniform_int_distribution<mt19937::result_type> dist(0, 6);
            num = dist(mt);
        }while(std::find(locations.begin(), locations.end(),num) == locations.end());
        return num;
    }

    vector<int> minimax(char** miniBoard, int depth, int alpha, int beta, bool maximizingPlayer){
        vector<int> valid_locations = get_valid_locations(miniBoard);
        vector<int> result;
        bool is_terminal = is_terminal_node(miniBoard);
        if (depth == 0 || is_terminal){
            //game is over
            if(is_terminal) {
                if (checkWin(miniBoard, aiPiece)) {
                     result.push_back(1000000);
                } else if (checkWin(miniBoard, playerPiece)) {
                    result.push_back(-1000000);
                } else {
                    result.push_back(0);
                }
            }
            //depth is 0
            else{
                result.push_back(scorePosition(aiPiece, playerPiece, miniBoard));
            }
        }
        else if(maximizingPlayer){
            int value = -1000000;
            int min = 1000000;
            int column = random_available_column(valid_locations);
            for(int i = 0; i< valid_locations.size(); i++){
                if(valid_locations[i] == -1){
                    continue;
                }
                char **tmpBoard = new char* [ROWS];
                for(int j = 0; j<ROWS; j++){
                    tmpBoard[j] = new char[COLS];
                }
                for(int j = 0; j<ROWS; j++){
                    for(int k = 0; k<COLS; k++){
                        tmpBoard[j][k] = miniBoard[j][k];
                    }
                }
                colChoice(i);
                takeTurn(tmpBoard, aiPiece, ROWS);
                vector<int> path = minimax(tmpBoard,depth-1, alpha, beta, false);
                if(path[0]>value) {
                    value = path[0];
                    column = i;
                }
                /*if(path[0]<min){
                    min = path[0];
                }*/
                if(i==(COLS/2)){
                    value += 2;
                }
                alpha = max(value,alpha);

                if(beta<=alpha){
                    break;
                }
            }
            result.push_back(value);
            result.push_back(alpha);
            result.push_back(beta);
            result.push_back(column);
        }
        else{
            int value = 1000000;
            int max = -1000000;
            int column = random_available_column(valid_locations);
            for(int i = 0; i< valid_locations.size(); i++){
                if(valid_locations[i] == -1){
                    continue;
                }
                char **tmpBoard = new char* [ROWS];
                for(int j = 0; j<ROWS; j++){
                    tmpBoard[j] = new char[COLS];
                }
                for(int j = 0; j<ROWS; j++){
                    for(int k = 0; k<COLS; k++){
                        tmpBoard[j][k] = miniBoard[j][k];
                    }
                }
                colChoice(i);
                takeTurn(tmpBoard, playerPiece, ROWS);
                vector<int> path = minimax(tmpBoard,depth-1,  alpha, beta, true);
                if(path[0]<value) {
                    value = path[0];
                    column = i;
                }
                /*
                if(path[0]<max){
                    max = path[0];
                }*/
                if(i == (COLS/2)){
                    value +=2;
                }
                beta = min(beta, value);


                if(beta<=alpha){
                    break;
                }


            }
            result.push_back(value);
            result.push_back(alpha);
            result.push_back(beta);
            result.push_back(column);

        }
        return result;
    }

    void play() {
    //loop for the turns
        char **board = new char* [ROWS];
        for(int i = 0; i<ROWS; i++){
            board[i] = new char[COLS];
        }
        initializeBoard(board);
        do {
            gameOver = false;
            printBoard(board);
            if(aiGame && aiTurn){
                aiTakeTurn(aiDifficulty, board);
            }
            else {
                colChoice(board);
                takeTurn(board, playerPiece, ROWS);
            }

            if (checkWin(board, playerPiece) || checkWin(board, aiPiece)) {
                playerWin(board);
                break;
            }
            if(checkTie(board)){
                gameOver = true;
                tieGame(board);
                break;
            }
            turnSwitch();

        } while (!gameOver);

    }
    void boardOptions(){
        char choice;
        int num;
        while(true) {
            cout << endl;
            cout << "       ----Board Options----" << endl;
            cout << "Number of Columns: C\n" << "Number of Rows: R\n" << "Length to Win: W\n" << "Exit: E" << endl;
            cout << "Please enter a character: " << endl;
            cin >> choice;
            if(toupper(choice) == 'R'){
                cout << "Enter number of rows: ";
                cin >> num;
                ROWS = num;
            }
            else if(toupper(choice) == 'C'){
                cout << "Enter number of rows: ";
                cin >> num;
                COLS = num;
            }
            else if(toupper(choice) == 'W'){
                do {
                    cout << "Enter number of pieces to win: ";
                    cin >> num;
                    WIN_LENGTH = num;
                    if(num>COLS && num >ROWS){
                        cout << "Too big. Win Length has to be smaller or equal to either rows or columns\n";
                    }
                }while(num>COLS && num >ROWS);
            }
            else if(toupper(choice) == 'E'){
                break;
            }
            else{
                cout << "Invalid Option, please try again" << endl;
            }

        }
    }
    void swapDifficulty(){
        char choice;
        while(true) {
            cout << endl;
            cout << "        -----Difficulty-----" << endl;
            cout << "Easy: N\n" << "Medium: M\n" << "Hard: H\n" << "Exit: E" << endl;
            cout << "Please enter a character: " << endl;
            cin >> choice;
            if(toupper(choice) == 'N'){
                aiDifficulty = 0;
            }
            else if(toupper(choice) == 'M'){
                aiDifficulty = 2;
            }
            else if(toupper(choice) == 'H'){
                aiDifficulty = 8;
            }
            else if(toupper(choice) == 'E'){
                break;
            }
            else{
                cout << "Invalid Option, please try again" << endl;
            }

        }

    }
    void optionsMenu(){
        char choice;
        while(true) {
            cout << "           -----Options-----" << endl;
            cout << "1 Player Game: 1" << endl;
            cout << "2 Player Game: 2" << endl;
            cout << "Change player symbols: C" << endl;
            cout << "Change the Board: B" << endl;
            cout << "Swap player order: S" << endl;
            cout << "Change difficulty: D" << endl;
            cout << "Exit Options: E" << endl;
            cout << "\n" << endl;
            cout << "Please enter a character:" << endl;
            cin >> choice;
            if(choice == '1'){
                aiGame = true;
            }
            else if(choice == '2'){
                aiGame = false;
            }
            else if(toupper(choice) == 'C'){
                pickSymbols();
            }
            else if(toupper(choice) == 'B'){
                boardOptions();
            }
            else if(toupper(choice) == 'S'){
                swapOrder();
            }
            else if(toupper(choice) == 'D'){
                swapDifficulty();
            }
            else if(toupper(choice) == 'E'){
                break;
            }
            else{
                cout << "Invalid Option, please try again" << endl;
            }
        }
    }

    void menu() {
        char choice;
        while (true) {
            cout << "-------Welcome to Connect 4-------" << endl;
            cout << "Play: P" << endl;
            cout << "Options: O " << endl;
            cout << "Exit: E" << endl;
            cout << "\n" << endl;
            cout << "Please enter a character to begin:" << endl;
            cin >> choice;
            if (toupper(choice) == 'P') {
                play();
            } else if (toupper(choice) == 'O') {
                optionsMenu();
            } else if (toupper(choice) == 'E') {
                break;
            } else {
                cout << "Invalid Option, please try again" << endl;
            }
        }
    }
};


#endif //PA02_TEMPLATE_CONNECT_4_H
