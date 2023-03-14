//
// Created by ethan on 2/22/2023.
//

#ifndef PA02_TEMPLATE_GAMELAUNCHER_H
#define PA02_TEMPLATE_GAMELAUNCHER_H

#include<iostream>
#include "board.h"
#include "player.h"

class gameLauncher {
private:
    board* gameBoard;

    //menu options that will impact game state
    bool aiGame = true;
    int rows = 6;
    int cols = 7;
    int win = 4;
    char p1symbol = '1';
    char p2symbol = '2';
    int aiDifficulty = 3;

public:
    gameLauncher();
    //play creates a board using all the option presets the menu allows me to change
    void play();
    //menu options, changing the game state
    void printMenu();
    void printOptions();
    void swapDifficulty();
    void boardOptions();
    void setPlayerSymbols();

};


#endif //PA02_TEMPLATE_GAMELAUNCHER_H
