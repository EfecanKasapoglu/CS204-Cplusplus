//
// Created by Efecan Kasapoglu on 12.05.2024.
//

#include "Player.h"

using namespace std;

Player::Player(Board& board, char symbol) : board(board),symbol(symbol) // this is my player class constructor
{
}

bool Player::put(int column){ // this function is used to place a symbol
    return board.put_piece(column,symbol);
}
void Player::turn_board(){ //this function rotates 90 degree clockwise
    board.turn_board_clockwise();
}
bool Player::is_winner() { // this checks if the player won the game
    return board.get_game_status()==symbol;
}

char Player::get_symbol() const{ // this function returns the symbol of the player
    return symbol;
}
