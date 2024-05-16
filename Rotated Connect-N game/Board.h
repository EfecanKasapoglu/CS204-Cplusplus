//
// Created by Efecan Kasapoglu on 12.05.2024.
//

#ifndef HW5_BOARD_H
#define HW5_BOARD_H


class Board { // this is for board class
private:
    int board_size; // dimension of the board
    int N; // required number of symbols to win
    char** board; // pointer to pointer of char

public:
    Board(int board_size,int N); // constructor
    ~Board();  // destructor
    void print_board(); // this funct prints the current board
    bool put_piece(int column,char symbol); // this funct puts the symbol but it also checks if it is implements or not
    void turn_board_clockwise(); //this funct rotates 90 degree clockwise
    char get_game_status(); //checks win conditions. I t returns symbols X/O or - and D
};


#endif //HW5_BOARD_H
