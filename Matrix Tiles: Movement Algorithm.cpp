// This homework created by Efecan Kasapoglu, 31038
// 23.02.2024, created time

#include <string>
#include <fstream> // for opening file
#include <vector>
#include <sstream>
#include <iostream>
using namespace std;

void printCurrentMatrix(const vector<vector<char>> & matrix){ //this function prints the current matrix
    for (int x=0; x<matrix.size(); x++){ //this is for the rows
        for (int y=0; y<matrix[0].size();y++){ //this is for the columns
            cout<<matrix[x][y];
        }
        cout<<endl;
    }
}

bool movementchecker(const vector<vector<char>> & matrix, int rowsize, int columnsize){//this function checks if there is a move possible or not
    for (int x=0; x<rowsize; x++) {
        for (int y=0; y<columnsize; y++) {
            if (matrix[x][y]=='r') {// Checks if there is a movement on right
                if (y==columnsize-1 || matrix[x][y+1]=='-') {
                    return true;
                }
            }

            else if (matrix[x][y]=='l') { //Checks if there is a movement on left
                if (y==0 || matrix[x][y-1]=='-') {
                    return true;
                }
            }
            else if (matrix[x][y]=='u') {//Checks if there is a movement on up
                if (x==0 ||matrix[x-1][y]=='-') {
                    return true;
                }
            }
            else if (matrix[x][y]=='d') {//Checks if there is a movement on down
                if (x==rowsize-1 || matrix[x+1][y]=='-') {
                    return true;
                }
            }
        }
    }
    return false; // No moves are possible
}


void rmovement(vector<vector<char>>& matrix, int row, int column, int rowsize, int columnsize) { // this function is for right movement
    int counter = 0; // this counter will count the space

    if (column==columnsize - 1) { // checks if the position is in the last column or not
        matrix[row][column] = '-';
        cout<<endl;
        cout<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
    } else if (matrix[row][column+1]!='-') { //checks if there is another letter in the next column
        cout<<endl;
        cout<<"No tiles have been moved."<<endl;
    } else {
        matrix[row][column]='-'; //clears the first position
        while (matrix[row][column+counter+1]=='-') { //counts space
            counter++;
        }
        if (column+counter+1==columnsize) { //checks if it is in the last column
            matrix[row][column+counter+1]='-';
        } else {
            matrix[row][column+counter]='r'; //if it is not in the last column it prints r in the current position
        }
        cout<<endl;
        cout<<"Tile at ("<<row<<","<<column<< ") has been moved."<<endl;
    }
}

void umovemnet(vector<vector<char>> &matrix, int row, int column) { // this function is for up movement
    int spacecounter=0;// this counter will count the space
    if (row == 0){// checks if the position is in the first row or not
        matrix[row][column]='-';
        cout<<endl;
        cout<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
    }
    else if (matrix[row-1][column]!='-'){//checks if there is another letter in the upper row
        cout<<endl;
        cout<<"No tiles have been moved."<<endl;
    }
    else {
        matrix[row][column]='-'; //clears the first position
        while (row-spacecounter>0 && matrix[row-spacecounter-1][column]=='-') {//counts space
            spacecounter++;
        }
        if (row-spacecounter==0){//checks if it is in the first row
            matrix[row][column]='-';
            cout<<endl;
            cout<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
        }
        else{
            matrix[row-spacecounter][column]='u';//if it is not in the first row it prints u in the current position
            cout<<endl;
            cout<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
        }

    }
}
void dmovement(vector<vector<char>> &matrix, int row, int column, int rowsize) {// this function is for down movement
    int spacecounter=0;// this counter will count the space
    if (row==rowsize-1) {// checks if the position is in the last row or not
        matrix[row][column]='-';
        cout<<endl<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
    } else if (matrix[row + 1][column] != '-'){//checks if there is another letter in the down row
        cout<<endl<<"No tiles have been moved."<<endl;
    } else {
        matrix[row][column]='-';
        if (matrix[row+spacecounter+1][column]=='-'){//counter is one if the down roll is space
            spacecounter=1;
        }

        while (row+spacecounter+1<rowsize && matrix[row+spacecounter+1][column]=='-') {//counts the space
            spacecounter++;
        }

        if (row+spacecounter+1!=rowsize && matrix[row+spacecounter+1][column]!='-') {//if it is not in the last row it prints d
            matrix[row+spacecounter][column]='d';
        }

        else if (row+spacecounter==rowsize) {// if it is in the last row
            matrix[row+spacecounter+1][column]='-';
        }
        cout<<endl<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
    }
}

void lmovement(vector<vector<char>>& matrix, int row, int column, int rowsize, int columnsize) {
    int counter=0;
    if (column==0) {//checks if it is in the first column
        matrix[row][column]='-';
        cout<<endl;
        cout<<"Tile at (" << row << "," << column << ") has been moved."<<endl;
    } else if (matrix[row][column-1] != '-') {// checks if there is a space after the letter
        cout<<endl;
        cout<<"No tiles have been moved."<<endl;
    } else {
        matrix[row][column]='-'; //Clears the current position
        while (column-counter-1>=0 && matrix[row][column-counter-1] == '-') {//counts the space
            counter++;
        }
        if (column-counter-1< 0) { //checks if it in the last column
            matrix[row][counter]='-';
        } else {
            matrix[row][column-counter]='l'; // checks if there is a letter left side or not
        }
        cout<<endl;
        cout<<"Tile at ("<<row<<","<<column<<") has been moved."<<endl;
    }
}
bool emptychecker(const vector<vector<char>> & matrix,int rowsize,int columnsize){
    int counter=0;
    for (int x=0; x<rowsize; x++){ //this for loop checks the characters of matrix. If the characters are different from "-,d,l,u,r" it gives error message and finishes the program.
        for (int y=0; y<columnsize;y++){
            if(matrix[x][y]=='-'){ //checks the matrix is empty or not
                counter++;
                if (counter==rowsize*columnsize){
                    return true;
                }
            }
        }
    }
    return false;
}
int main() {
    int counter=0;
    int row,column;
    string fileName,line;
    vector<vector<char>> matrixFile; //creating empty matrix
    cout<<"Please enter the file name: "; // taking the file name
    cin>>fileName;

    ifstream input;
    input.open(fileName.c_str());//opening the file

    while ( input.fail()){ // if it fails to open the file
        cout<<endl;
        cout<<"Could not open the file. Please enter a valid file name: "; // printing that it is failed and taking the file again
        cin>>fileName;
        input.open(fileName.c_str()); //opening the file again

    }

    while(!input.eof()){  // this while loop reads line by line. Reads line to a character vector and appends to the main vector
        getline(input,line); //gets the line
        stringstream ss(line);
        char character;
        vector<char> temporary; //creates temporary matrix
        while (ss>>character){ //takes the character into temporary vector
            temporary.push_back(character);

        }
        matrixFile.push_back(temporary);//it appends the temporary vector to the main vector
        if (matrixFile[0].size() != temporary.size()){ //checks the size
            cout<<endl;
            cout<<"Erroneous file content. Program terminates.";
            return 0;
        }
    }
    int rowsize=matrixFile.size(); //rows size
    int columsize=matrixFile[0].size(); // columns size

    for (int x=0; x<rowsize; x++){ // this for loop checks the characters of matrix. If the characters are different from "-,d,l,u,r" it gives error message and finishes the program.
        for (int y=0; y<columsize;y++){
            if (!(matrixFile[x][y] == '-' || matrixFile[x][y] == 'd' || matrixFile[x][y] == 'l' || matrixFile[x][y] == 'u' || matrixFile[x][y] == 'r')) {
                cout<<endl;
                cout<<"Erroneous file content. Program terminates.";
                return 0;
            }
            if(matrixFile[x][y]=='-'){ //checks the matrix is empty or not
                counter++;
                if (counter==rowsize*columsize){
                    cout<<endl;
                    cout<<"The matrix file contains:"<<endl;
                    printCurrentMatrix(matrixFile);
                    cout<<"The matrix is empty.";
                    return 0;
                }
            }
        }
    }
    cout<<endl;
    cout<<"The matrix file contains:"<<endl;
    printCurrentMatrix(matrixFile); //prints the current matrix
    if(!movementchecker(matrixFile,rowsize,columsize)){//checks if there is a move possible or not
        cout<<"No more moves are possible.";
        return 0;
    }
    cout<<"Please enter the row and column of the tile that you want to move: "; //takes the row and column input
    cin>>row>>column;
    while(row>=rowsize||row<0||column<0||column>=columsize){ //checks the input is is valid or not
        cout<<endl;
        cout<<"Invalid row or column index."<<endl;
        cout<<"Please enter the row and column of the tile that you want to move: ";
        cin>>row>>column;
    }
    while (!emptychecker(matrixFile, rowsize, columsize) && movementchecker(matrixFile, rowsize, columsize)) { //game starts here. while is not empty and there are possible moves game is going to play

        if (matrixFile[row][column] == 'r') {//for r
            rmovement(matrixFile, row, column, rowsize,columsize);
            printCurrentMatrix(matrixFile);
        } else if (matrixFile[row][column] == 'u') {//for u
            umovemnet(matrixFile, row, column);
            printCurrentMatrix(matrixFile);
        } else if (matrixFile[row][column] == 'd') {// for d
            dmovement(matrixFile, row, column, rowsize);
            printCurrentMatrix(matrixFile);
        } else if (matrixFile[row][column] == 'l') {// for l
            lmovement(matrixFile,row,column,rowsize,columsize);
            printCurrentMatrix(matrixFile);
        }
        else if(matrixFile[row][column]=='-'){// for -
            cout<<endl;
            cout<<"No tiles have been moved."<<endl;
            printCurrentMatrix(matrixFile);
        }
        if (!emptychecker(matrixFile, rowsize, columsize)&& movementchecker(matrixFile, rowsize, columsize)){//if matrix is not empty or there are still moves possible than game continues and takes new rol and column input
            cout << "Please enter the row and column of the tile that you want to move: ";
            cin >> row >> column;
            while (row >= rowsize||row < 0||column<0 || column>=columsize) {//checks input
                cout<<endl;
                cout<<"Invalid row or column index."<<endl;
                cout<<"Please enter the row and column of the tile that you want to move: ";
                cin>>row>>column;
            }
        }
    }
    if (emptychecker(matrixFile, rowsize, columsize)){//if matrix is empty
        cout<<"The matrix is empty.";
        return 0;
    }

    if(!movementchecker(matrixFile, rowsize, columsize)){//if movement possible or not
        cout<<"No more moves are possible.";
        return 0;
    }
    return 0;
}
