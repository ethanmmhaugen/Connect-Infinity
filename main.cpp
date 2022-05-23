#include <iostream>
//Ethan Haugen 5/20/2022 Complete, unbreakable connect 4 code
const int COLS = 7;
const int ROWS = 6;

//creates the empty board
void initializeBoard(char board[][COLS]){
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = '_';
        }
    }
}

//Prints the board array with the lines and such
void printBoard(char board[][COLS]){
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            std::cout << "|" << board[i][j];
        }
        std::cout << '|' << std::endl;
    }
}

//Lets 2 players pick characters one after another. Repeat characters aren't allowed
void pickSymbols(char pTurn[]){
    std::cout << "Enter Player 1's Character:\n";
    std::cin >> pTurn[0];
    do{
        std::cout << "Enter Player 2's Character:\n";
        std::cin >> pTurn[1];
        if(pTurn[1] == pTurn[0]){
            std::cout << "Nice try breaking my code. Please pick a different character for Player 2...\n";
        }
    } while (pTurn[1] == pTurn[0]);

}

//switches which players turn it is, connects to a char array that has the characters stored
int turnSwitch(int t){
    if (t == 0) {
        t += 1;
    } else {
        t -= 1;
    }
    return t;
}

//checks if a column has empty spots left
bool colCheck(int move, char board[][COLS]) {
    bool spacecounter = false;
    for (int i = 0; i < ROWS; i++) {
        if (board[i][move] == '_') {
            spacecounter = true;
        }
    }
    if (spacecounter) {
        return true;
    }
    std::cout << "That Column is full. Please pick another column... \n";
    return false;
}

//Lets user pick a column and sends it to column checker before returning the confirmed valid column
int colChoice(char board[][COLS]){
    int move = 0;
    bool isValid;
    do {
        std::cout << "Choose a column 1-7:\n";
        std::cin >> move;
        move -= 1;
        if (move > 6 || move < 0) {
            std::cout << "Invalid Choice.";
            continue;
        }
        isValid = colCheck(move,board);
    } while(move > 6 || move < 0 || !isValid);

    return move;
}

//sends the confirmed column to the board array in the lowest available row
int takeTurn(char board[][COLS],int move,int t,char pTurn[]){
    int moverow;
    for (int i = ROWS; i > -1; i--) {
        if (board[i][move] == '_') {
            board[i][move] = pTurn[t];
            moverow = i;
            break;
        }
    }
    return moverow;
}

//declares the winner and allows the turn loop to break
void playerWin(char board[][COLS], int t, bool& gameOver){
    printBoard(board);
    std::cout << "Game Over!! Player " << t + 1 << " is the Winner!\n";
    gameOver = true;
}

//checks all win conditions and calls playerWin if there is a win
void checkWin(char board[][COLS], int moverow, int move, int pTurn, bool&gameOver) {
    bool win;
    //check horizontal win conditions
    for (int j = 0; j < COLS - 3; j++) {
        if (board[moverow][j] != '_' && board[moverow][j] == board[moverow][j + 1]
            && board[moverow][j] == board[moverow][j + 2]
            && board[moverow][j] == board[moverow][j + 3]) {
            win = true;
        }
    }
    //check vertical win conditions
    for (int i = 0; i < ROWS - 3; i++) {
        if (board[i][move] != '_' && board[i][move] == board[i + 1][move] && board[i][move] == board[i + 2][move] &&
            board[i][move] == board[i + 3][move]) {
            win = true;
        }
    }
    //check diagonal win conditions
    for (int i = 3; i < ROWS; i++) {
        for (int j = 0; j < COLS - 3; j++) {
            if (board[moverow][move] == board[moverow + 1][move + 1] &&
                board[moverow][move] == board[moverow + 2][move + 2] &&
                board[moverow][move] == board[moverow + 3][move + 3]) {
                win = true;
            }
        }
        for (int j = 3; j < COLS; j++) {
            if (board[moverow][move] == board[moverow - 1][move + 1] &&
                board[moverow][move] == board[moverow - 2][move + 2] &&
                board[moverow][move] == board[moverow - 3][move + 3]) {
                win = true;
            }
        }
    }
    if (win) {
        playerWin(board, pTurn, gameOver);
    }
}

//Prints tie game and breaks the game loop
void tieGame(char board[][COLS], bool& gameOver){
    printBoard(board);
    std::cout << "Game Over!! Tie!!\n";
    gameOver = true;
}

//checks for tie and calls tieGame if its tied
void checkTie(char board[][COLS], bool& gameOver){
    int tiecounter = 0;
    for(int i = 0; i<ROWS; i++){
        for(int j = 0; j<COLS; j++){
            if(board[i][j] != '_') {
                tiecounter += 1;
            }
        }
        if(tiecounter == (ROWS*COLS)){
            tieGame(board, gameOver);
        }
    }
}

//allows user to play again or break out of the play loop to end the program
char playAgain(){
    char again;
    do {
        std::cout << "Would you like to play again? Type Y for Yes or N for No:\n";
        std::cin >> again;
        if (again != 'Y' && again != 'N') {
            std::cout << "Wrong Input.\n";
        }
    } while (again != 'Y' && again != 'N');
    return again;
}

int main() {
    char again;
    char board[ROWS][COLS];
    char turn[2];
    bool gameOver = false;


    //encompassing loop to allow play again feature
    do {
        pickSymbols(turn);
        int pTurn = 0;
        initializeBoard(board);

        //loop for the turns
        do {
            gameOver = false;

            printBoard(board);

            int choice = colChoice(board);
            int moverow = takeTurn(board, choice, pTurn, turn);

            checkWin(board, moverow, choice, pTurn, gameOver);

            checkTie(board,gameOver);

            pTurn = turnSwitch(pTurn);

        } while(!gameOver);
        again = playAgain();

    } while(again == 'Y');
}

//Input: characters for players
// Processing: board setup, take turn, check win, declare winner, switch players, error checking
//output: print board, print winner/gameover