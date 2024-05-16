//
// Created by Efecan Kasapoglu on 12.05.2024.
//
#include <iostream>
#include <string>
#include "Board.h"
using namespace std;

Board::Board(int board_size,int N):board_size(board_size),N(N){ // board class constructor.
    board=new char*[board_size]; // allocates memory for row
    for(int i=0;i<board_size;i++){
        board[i]=new char[board_size]; // allocates memory for column
        for(int j=0;j<board_size;j++){
            board[i][j]='-'; // puts - in the board
        }
    }
}

Board::~Board(){ // this destructor
    int x=0;
    while(x<board_size){
        delete[] board[x]; //deletes all the columns
        x++;
    }
    delete[] board; // deletes all the rows
}

void Board::print_board(){ // prints the current board
    cout<<endl;
    for(int x=0; x<board_size;x++){
        for(int y=0;y<board_size;y++){
            cout<<board[x][y]; //prints each cell
        }
        cout<<endl;
    }
    cout<<endl;
}

bool Board::put_piece(int column,char symbol){  //puts the symbol in the board. However, if the column is full then it goes false
    if(column>=0&&column<board_size){ // checks the column exists or not
        int x=board_size-1; // this is for starting at the last row
        while(x>=0){
            if(board[x][column]=='-'){  // if it finds a valid place
                board[x][column]=symbol; // it changes the place with the symbol
                return true; // it goes true if it completed
            }
            else{
            }
            x--;
        }
        return false; // this is for not empty space
    }
    else{
        return false; // column does not exits
    }
}

void Board::turn_board_clockwise(){ // rotates the board in 90 degree clockwise
    char** newboard= new char*[board_size]; // creates new board for the row
    for(int x=0; x<board_size;x++){
        newboard[x]=new char[board_size]; // creates new board for the column
    }
    for(int x=0;x<board_size;x++){ // rotates 90 degree
        for(int y=0; y<board_size;y++){
            newboard[y][-x-1+board_size]=board[x][y];
        }
    }
    for (int y=0;y<board_size;y++){ // after rotation it drops the index if there is an exist place
        for(int x=board_size-1;x>0;x--){
            if(newboard[x][y]=='-'&&newboard[x-1][y]!='-'){ // if there is an empty place
                int dropind=x; // this part counts the empty places
                while(dropind<board_size&&newboard[dropind][y]=='-'){
                    dropind++;
                }
                newboard[dropind-1][y]=newboard[x-1][y];
                newboard[x-1][y]='-';
            }
        }
    }
    int x=0;
    while(x<board_size){ // this part deletes the column
        delete[] board[x];
        x++;
    }
    delete[] board; // deletes the row
    board=newboard; // makes the new rotated row as a main board
}

char Board::get_game_status() { // this funct checks the status of the game. It will look for winner, draw or the game still goes
    bool Xwinner=false,Owinner=false,empty=false; // I created this functions becasue I will check the conditions after the exam
    for(int x=0;x<board_size;x++){// this 2 for loops checks all the rows and the columns
        int Xvert=0,Overt=0,Xhor=0,Ohor=0;//counters for symbols for both vertical and horizontal
        for(int y=0;y<board_size;y++){
            if(board[y][x]=='X'){// checks vertical for X wins
                Xvert++;
            }
            else{//resets the counter
                Xvert=0;
            }
            if(board[y][x]=='O'){// checks vertical for O wins
                Overt++;
            }
            else{//resets the counter
                Overt=0;
            }
            if(Xvert==N){// if x vertical counter is equal to the N
                Xwinner=true;// then it goes true
            }
            if(Overt==N){// if o vertical counter is equal to the N
                Owinner=true;// then it goes true
            }
            if(board[x][y]=='X'){// checks horizontal for X wins
                Xhor++;
            }
            else{//resets the counter
                Xhor=0;
            }
            if(board[x][y]=='O'){// checks horizontal for O wins
                Ohor++;
            }
            else{
                Ohor=0;//resets the counter
            }
            if(Xhor==N){// if x horizontal counter is equal to the N
                Xwinner=true;
            }
            if(Ohor==N){// if O horizontal counter is equal to the N
                Owinner=true;
            }
            if(board[x][y]=='-'){//checks for the empty place. If there is an empty place than it goes tru
                empty=true;
            }
        }
    }
    for(int x=0;x<=board_size-N;x++){//this loop is for diagonal check
        for(int y=0;y<=board_size - N;y++){
            int XdiaLR=0,OdiaLR=0,XdiaRL=0,OdiaRL=0;//counters for diagonal
            for(int k=0;k<N;k++){//left to right check
                if(board[x+k][y+k]=='X'){//checks for X
                    XdiaLR++;
                }
                else{//resets the counter
                    XdiaLR=0;
                }
                if(board[x+k][y+k]=='O'){//checks for O
                    OdiaLR++;
                }
                else{//resets the counter
                    OdiaLR=0;
                }

                if(x+k<board_size && y+k<board_size && y-k>=0){//diagonal check for right to left
                    if(board[x+k][y-k]=='X'){//diag check for X
                        XdiaRL++;
                    }
                    else{//resets counter
                        XdiaRL=0;
                    }

                    if(board[x+k][y-k]=='O'){//diag check for O
                        OdiaRL++;
                    }
                    else{
                        OdiaRL=0;
                    }
                }

                if(XdiaLR==N || XdiaRL==N){//returns true if X wins diagonal
                    Xwinner=true;
                }
                if(OdiaLR==N || OdiaRL==N){//returns true if O wins diagonal
                    Owinner=true;
                }
            }
        }
    }

    if(Xwinner && Owinner){//if x and o both wins then D returns
        return 'D';
    }
    else if(Xwinner){//if x wins x returns
        return 'X';
    }
    else if(Owinner){//if o wins O returns
        return 'O';
    }
    else if(empty){//if empty space found(game still continues) then - returns
        return '-';
    }
    return 'D';//for other conditions which is not stated in the top
}
