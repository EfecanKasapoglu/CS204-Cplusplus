//
// Created by Efecan Kasapoglu on 12.05.2024.
//

#ifndef HW5_PLAYER_H
#define HW5_PLAYER_H
#include "Board.h"

class Player { //class of the player
private:
    Board& board; //ref to the gameboard
    char symbol; //the players symbol

public:
    Player(Board& board, char symbol); // constructor
    bool put(int column); //used to place the players symbol. checks if it is done or not. that is why it is in bool function
    void turn_board(); // this funct rotates the board in clockwise
    bool is_winner(); //this funct checks if the player won the game or not. that is why it is in bool function
    char get_symbol() const; //this funct return the symbol of the player
};


#endif //HW5_PLAYER_H
