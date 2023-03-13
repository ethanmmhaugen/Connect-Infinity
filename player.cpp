//
// Created by ethan on 2/22/2023.
//

#include "player.h"
#include "board.h"


void player::takeTurn(int rows, int COLS, board& myBoard) {
    int columnChoice;
    do {
        cout << "Please Enter a Column 1-" << myBoard.getRows() + 1 << endl;
        cin >> columnChoice;
        columnChoice--;
        if (!myBoard.checkColumn(columnChoice)) {
            cout << "That Column is Full!!" << endl;
        }
    }while(columnChoice<-1 || columnChoice>rows || !myBoard.checkColumn(columnChoice));
    playerMove[0] = myBoard.findRow(columnChoice);
    playerMove[1] = columnChoice;

}

aiPlayer::aiPlayer(char p, int num) {
    piece = p;
    playerNum = num;
}

void aiPlayer::takeTurn(int ROWS, int COLS, board& myBoard){
    //Random column selection
    cout << endl;
    if(aiDifficulty == 0){
        random_device rand;
        mt19937 mt(rand());
        uniform_int_distribution<mt19937::result_type> dist(0,(COLS-1));
        colChoice(dist(mt));
    }


        //This is medium difficulty bot
        // colChoice(pick_best_move(board, aiPiece, playerPiece));
    else {
        vector<int> result = minimax(myBoard, aiDifficulty, -1000000, 1000000, true);
        colChoice(result[3]);
    }
    //Time delay before taking turn
    //sleep_for(seconds(2));

    //Take the turn
    findRow(myBoard, ROWS);
}

void player::colChoice(int i) {
    playerMove[1] = i;
}

void player::findRow(board& myBoard, int rows){
    for (int i = rows-1; i > -1; i--) {
        if (myBoard.getBoard()[i][playerMove[1]] == '_') {
            myBoard.getBoard()[i][playerMove[1]] = piece;
            playerMove[0] = i;
            break;
        }
    }
}

void player::setDifficulty(int i) {

}


vector<int> aiPlayer::minimax(board& miniBoard, int depth, int alpha, int beta, bool maximizingPlayer){
    vector<int> valid_locations = miniBoard.get_valid_locations();
    vector<int> result;
    int ROWS = miniBoard.getRows();
    int COLS = miniBoard.getCols();
    int WIN_LENGTH = miniBoard.getWinLength();
    char playerPiece = miniBoard.getPlayerPiece();
    char aiPiece = piece;
    bool is_terminal = miniBoard.is_terminal_node();
    if (depth == 0 || is_terminal){
        //game is over
        if(is_terminal) {
            if (miniBoard.checkwin(aiPiece)) {
                result.push_back(1000000);
            } else if (miniBoard.checkwin(playerPiece)) {
                result.push_back(-1000000);
            } else {
                result.push_back(0);
            }
        }
            //depth is 0
        else{
            //miniBoard.printBoard();
            //cout << scorePosition(aiPiece, playerPiece, miniBoard);
            result.push_back(scorePosition(aiPiece, playerPiece, miniBoard));
        }
    }
    else if(maximizingPlayer){
        int value = -1000000;
        int column = miniBoard.random_available_column(valid_locations);
        /*for(int k = 0; k<2-depth; k++){
            cout << "  ";
        }
        cout << "Maximizing player: Depth is " << depth << endl;
         */
        for(int i = 0; i< valid_locations.size(); i++){
            if(valid_locations[i] == -1){
                continue;
            }
            board tmpBoard = board(miniBoard);
            colChoice(i);
            findRow(tmpBoard, ROWS);
            tmpBoard.placePiece(playerMove[0], playerMove[1], aiPiece);
            tmpBoard.turnSwitch();
            vector<int> path = minimax(tmpBoard,depth-1, alpha, beta, false);
            /*for(int k = 0; k<2-depth; k++){
                cout << "  ";
            }
             */
            if(path[0]>value) {
                value = path[0];
                column = i;
            }
            //cout << "Col " << i+1 << " has value of " << path[0] << endl;
            /*if(path[0]<min){
                min = path[0];
            }*/
            alpha = max(value,alpha);

            if(beta<=alpha){
                break;
            }
        }
        //cout << endl;
        result.push_back(value);
        result.push_back(alpha);
        result.push_back(beta);
        result.push_back(column);
    }
    else{
        int value = 1000000;
        int column = miniBoard.random_available_column(valid_locations);
        /*for(int k = 0; k<2-depth; k++){
            cout << "  ";
        //cout << "Minimizing player: Depth is " << depth << endl;
         */
        for(int i = 0; i< valid_locations.size(); i++){
            if(valid_locations[i] == -1){
                continue;
            }
            board tmpBoard = board(miniBoard);
            colChoice(i);
            findRow(tmpBoard, ROWS);
            tmpBoard.placePiece(playerMove[0], playerMove[1], playerPiece);
            tmpBoard.turnSwitch();
            vector<int> path = minimax(tmpBoard,depth-1,  alpha, beta, true);
            if(path[0]<value) {
                value = path[0];
                column = i;
            }
            /*
            if(path[0]<max){
                max = path[0];
            }*/
            /*for(int k = 0; k<2-depth; k++){
                cout << "  ";
            }
             */
            //cout << "Col " << i+1 << " has value of " << path[0] << endl;
            beta = min(beta, value);


            if(beta<=alpha){
                break;
            }
        }
        //cout << endl;
        result.push_back(value);
        result.push_back(alpha);
        result.push_back(beta);
        result.push_back(column);

    }
    return result;
}

int aiPlayer::scorePosition(char piece, char opponents_piece, board& scoringBoard) {
    int score = 0;
    //Score horizontals
    char** board = scoringBoard.getBoard();
    int rows = scoringBoard.getRows();
    int cols = scoringBoard.getCols();
    int win = scoringBoard.getWinLength();
    for (int i = 0; i < rows; i++) {
        //array of individual rows
        char row_array[cols];
        for (int j = 0; j < cols; j++) {
            row_array[j] = board[i][j];
        }
        //Window of 4 pieces at a time that we look at for score,
        // iterate through and count the pieces
        for (int c = 0; c < cols - (win - 1); c++) {
            //Here we check each window
            int pieceCount = 0;
            int spaceCount = 0;
            int opponentCount = 0;
            for (int p = c; p < c + win; p++) {
                if (row_array[p] == piece) {
                    pieceCount++;
                } else if (row_array[p] == opponents_piece) {
                    opponentCount++;
                } else {
                    spaceCount++;
                }

            }

            //now check scores in that window
            if (pieceCount == win) {
                score += 100;
            } else if (opponentCount == (win - 1) && spaceCount == 1) {
                score -= 200;
            } else if (pieceCount == (win - 1) && spaceCount == 1) {
                score += 5;
            } else if (pieceCount == (win - 2) && spaceCount == 2) {
                score += 2;
            }
        }
    }

    //vertical score checking
    for(int i = 0; i<cols; i++){
        //array of individual rows
        char col_array[rows];
        for(int j = 0; j<rows; j++){
            col_array[j] = board[j][i];
        }
        //Window of 4 pieces at a time that we look at for score,
        // iterate through and count the pieces
        for(int c = 0; c<rows-(win-1); c++){
            //Here we check each window
            int pieceCount = 0;
            int spaceCount = 0;
            int opponentCount = 0;
            for(int p = c; p<c+win; p++){
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
            if(pieceCount == win){
                score+=100;
            }
            else if(opponentCount == (win-1) && spaceCount == 1){
                score-=200;
            }
            else if(pieceCount == (win-1) && spaceCount == 1){
                score+=5;
            }
            else if(pieceCount == (win-2) && spaceCount == 2){
                score+=2;
            }
        }
    }

    //score negative slope diagonals
    for(int i = 0; i<rows-(win-1); i++){
        for(int j = 0; j<cols-(win-1); j++){
            int pieceCount = 0;
            int spaceCount = 0;
            int opponentCount = 0;
            for(int c = 0; c<win; c++) {
                char spot = board[i+c][j+c];
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
            if(pieceCount == win){
                score+=100;
            }
            else if(opponentCount == (win-1) && spaceCount == 1){
                score-=200;
            }
            else if(pieceCount == (win-1) && spaceCount == 1){
                score+=5;
            }
            else if(pieceCount == (win-2) && spaceCount == 2){
                score+=2;
            }
        }
    }

    //score positive slope diagonals
    for(int i = (win-1); i<rows; i++){
        for(int j = 0; j<cols-(win-1); j++){
            int pieceCount = 0;
            int spaceCount = 0;
            int opponentCount = 0;
            for(int c = 0; c<win; c++) {
                char spot = board[i-c][j+c];
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
            if(pieceCount == win){
                score+=100;
            }
            else if(opponentCount == (win-1) && spaceCount == 1){
                score-=200;
            }
            else if(pieceCount == (win-1) && spaceCount == 1){
                score+=5;
            }
            else if(pieceCount == (win-2) && spaceCount == 2){
                score+=2;
            }
        }
    }
    for(int i = 0; i<rows; i++){
        if(board[i][3] == piece){
            score+=1;
        }
    }

    return score;
}

