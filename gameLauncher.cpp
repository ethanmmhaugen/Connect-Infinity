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
    gameBoard = new board(rows, cols, win, aiGame, p1symbol, p2symbol, aiDifficulty);
    gameBoard->resetBoard();
    do {
        gameBoard->takeTurn();
        gameBoard->turnSwitch();
        //Check win conditions for current player's piece
    }while(!gameBoard->checkwin(gameBoard->getPrevPlayer()->getPiece()) && !gameBoard->checkTie());
    if(!gameBoard->checkTie()){
        gameBoard->declareWinner();
    }
    else{
        gameBoard->declareTie();
    }


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
            gameBoard->turnSwitch();
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
        switch(toupper(choice)){
            case 'N':
                aiDifficulty = 0;
                break;
            case 'M':
                aiDifficulty = 3;
                break;
            case 'H':
                aiDifficulty = 8;
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
            cin >> rows;
        } else if (toupper(choice) == 'C') {
            cout << "Enter number of columns: ";
            cin >> cols;
        } else if (toupper(choice) == 'W') {
            do {
                cout << "Enter number of pieces to win: ";
                cin >> num;
                if (num > cols && num > rows) {
                    cout << "Too big-> Win Length has to be smaller or equal to either rows or columns\n";
                }
            } while (num > cols && num > rows);
            win = num;
        } else if (toupper(choice) == 'E') {
            break;
        } else {
            cout << "Invalid Option, please try again" << endl;
        }

    }
}
void gameLauncher::setPlayerSymbols() {
    cout << "Enter Player 1's Symbol: " << endl;
    cin >> p1symbol;
    cout << "Enter Player 2's Symbol: " << endl;
    cin >> p2symbol;
}

