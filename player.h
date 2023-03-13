//
// Created by ethan on 1/15/2023.
//

#ifndef PA02_TEMPLATE_PLAYER_H
#define PA02_TEMPLATE_PLAYER_H

#include <vector>
#include <iostream>
#include <random>

using namespace std;

class board;

class player{
private:
protected:
    char piece;
    int playerMove[2] = {0,0};
    int playerNum;
public:
    player()= default;

    player(char p, int num){
        piece = p;
        playerNum = num;
    }
    ~player() = default;
    virtual void takeTurn(int rows, int COLS, board& myBoard);

    void colChoice(int i);

    void findRow(board& myBoard, int rows);
    void setPlayerNum(int i){
        playerNum = i;
    }
    void setPiece(char p){
        piece = p;
    }

    char getPiece() const{
        return piece;
    }

    int getPlayerNum() const{
        return playerNum;
    }

    int* getPlayerMove(){
        return playerMove;
    }


    virtual void setDifficulty(int i);
};

class aiPlayer : public player{
private:

    int aiDifficulty = 3;
public:
    aiPlayer(char p, int num);

    void setDifficulty(int i) override{
        aiDifficulty = i;
    }
    int getDifficulty() const{
        return aiDifficulty;
    }
    void takeTurn(int rows, int COLS, board& myBoard) override;

    vector<int> minimax(board& miniBoard, int depth, int alpha, int beta, bool maximizingPlayer);
    int scorePosition(char piece, char opponents_piece, board& scoringBoard);
};

#endif //PA02_TEMPLATE_PLAYER_H
