//
// Created by ethan on 2/22/2023.
//

#include "gameLauncher.h"

gameLauncher::gameLauncher(){

}
void gameLauncher::printMenu() {
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
            printOptions();
        } else if (toupper(choice) == 'E') {
            break;
        } else {
            cout << "Invalid Option, please try again" << endl;
        }
    }
}

void gameLauncher::play(){
    gameBoard = board(rows, cols, win, aiGame);
    gameBoard.resetBoard();
    do {
        gameBoard.takeTurn();
        gameBoard.turnSwitch();
        //Check win conditions for current player's piece
    }while(!gameBoard.checkwin(gameBoard.getPrevPlayer()->getPiece()));
    gameBoard.declareWinner();

}

void gameLauncher::printOptions(){
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
            setPlayerSymbols();
        }
        else if(toupper(choice) == 'B'){
            boardOptions();
        }
        else if(toupper(choice) == 'S'){
            gameBoard.turnSwitch();
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

void gameLauncher::swapDifficulty(){
    char choice;
    while(true) {
        cout << endl;
        cout << "        -----Difficulty-----" << endl;
        cout << "Easy: N\n" << "Medium: M\n" << "Hard: H\n" << "Exit: E" << endl;
        cout << "Please enter a character: " << endl;
        cin >> choice;
        int n;
        switch(toupper(choice)){
            case 'N':
                n = 0;
                break;
            case 'M':
                n = 2;
                break;
            case 'H':
                n = 8;
                break;
            case 'E':
                return;
            default:
                cout << "Invalid Option, please try again" << endl;
                continue;
        }

    }

}

void gameLauncher::boardOptions() {
    char choice;
    int num;
    while (true) {
        cout << endl;
        cout << "       ----Board Options----" << endl;
        cout << "Number of Columns: C\n" << "Number of Rows: R\n" << "Length to Win: W\n" << "Exit: E" << endl;
        cout << "Please enter a character: " << endl;
        cin >> choice;
        if (toupper(choice) == 'R') {
            cout << "Enter number of rows: ";
            cin >> num;
            gameBoard.setRows(num);
        } else if (toupper(choice) == 'C') {
            cout << "Enter number of columns: ";
            cin >> num;
            gameBoard.setCols(num);
        } else if (toupper(choice) == 'W') {
            do {
                cout << "Enter number of pieces to win: ";
                cin >> num;
                if (num > gameBoard.getCols() && num > gameBoard.getRows()) {
                    cout << "Too big. Win Length has to be smaller or equal to either rows or columns\n";
                }
            } while (num > gameBoard.getCols() && num > gameBoard.getRows());
            gameBoard.setWinLength(num);
        } else if (toupper(choice) == 'E') {
            break;
        } else {
            cout << "Invalid Option, please try again" << endl;
        }

    }
}
void gameLauncher::setPlayerSymbols() {
    char symbol;
    cout << "Enter Player 1's Symbol: " << endl;
    cin >> symbol;
    gameBoard.setP1(symbol);
    cout << "Enter Player 2's Symbol: " << endl;
    cin >> symbol;
    gameBoard.setP2(symbol);
}

