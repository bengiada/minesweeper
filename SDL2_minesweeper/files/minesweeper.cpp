#include <iostream>
#include <queue>
#include "minesweeper.h"

void MineSweeper::destroyBoard(){
    
    for(int i = 0; i < size; i++){
        delete board[i];
        delete visible[i];
    }
    delete board; //Creates board
    delete visible;
}

void MineSweeper::generateBoard(int Size, int Mine){
    size = Size;
    mineCount = Mine;
    uncoveredcells = 0;
    flaggedCount = 0;
    game = true;

    
    board = new char*[size]; //Creates board
    visible = new char*[size];
    for(int i = 0; i < size; i++){
        board[i] = new char[size];
        visible[i] = new char[size];

        for(int j = 0; j < size; j++){
            board[i][j] = '0';
            visible[i][j] = invisible;
        }
    }
    
    //Assigns mineCount mines randomly
    int count = 0, x, y;
    srand((unsigned)time(NULL));
    
    while(count < mineCount){
        x = rand() % size;
        y = rand() % size;
        
        if(board[x][y] != 'X'){
            board[x][y] = 'X';
            
            for(int i = x-1; i < x+2; i++){
                for(int j = y-1; j < y+2; j++){
                    updateCell(i, j);
                }
            }
            count++;
        }
        
    }
}

void MineSweeper::updateCell(int i, int j){
    if(i >= 0 && i < size && j >= 0 && j < size && board[i][j] != 'X'){
        board[i][j] = board[i][j] + 1;
    }
}

void MineSweeper::printBoard(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cout << visible[i][j] << " ";
        }
        std::cout << std::endl;

    }
}

void MineSweeper::startGame(){
    char type;
    
    while(game && uncoveredcells < size*size - mineCount){
        //get input
        std::cout << "Please enter type: (P to play, F to flag)\n";
        std::cin >> type;
        
        if(type == 'P'){
            //play();
        }
        else if(type == 'F'){
            //flag();
        }
        else{
            std::cout << "Wrong type input\n";
        }
    
        //printBoard();

    }
}

void MineSweeper::makeVisible(int i, int j){
    if(game){
        if(visible[i][j] == invisible){
            uncoveredcells++;
        }
    }
    visible[i][j] = board[i][j];

    
}

void MineSweeper::makeEverythingVisible(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            makeVisible(i,j);
        }
    }
    
}

void MineSweeper::play(int i, int j){
    //int i, j;
    //std::cin >> i >> j;
    
    //if it is a valid input
    if(i < 0 || i >= size || j < 0 || j >= size){
        std::cout << "Wrong input" << std::endl;
        return;
    }
    
    if(visible[i][j] == flagged){
        return;
    }
    
    //placing on a 'X'
    if(board[i][j] == 'X'){
        std::cout << "GAME OVER" << std::endl;
        makeEverythingVisible();
        game = false;
    }

    //placing on other cells
    else{
        std::queue<std::pair<int,int> > q;
        
        q.push(std::make_pair(i,j));
        int curr_y, curr_x;
        
        while(!q.empty()){ //uncovers all adjacent 0's
            curr_y = q.front().first;
            curr_x = q.front().second;
            q.pop();
            makeVisible(curr_y, curr_x);

            if(board[curr_y][curr_x] == '0'){
                if(curr_x > 0){
                    if(visible[curr_y][curr_x-1] == invisible){
                        makeVisible(curr_y, curr_x-1);
                        q.push(std::make_pair(curr_y, curr_x-1));
                    }
                }
                if(curr_x < size-1){
                    if(visible[curr_y][curr_x+1] == invisible){
                        makeVisible(curr_y, curr_x+1);
                        q.push(std::make_pair(curr_y, curr_x+1));
                    }
                }
                if(curr_y > 0){
                    if(visible[curr_y-1][curr_x] == invisible){
                        makeVisible(curr_y-1, curr_x);
                        q.push(std::make_pair(curr_y-1, curr_x));
                    }
                }
                if(curr_y < size-1){
                    if(visible[curr_y+1][curr_x] == invisible){
                        makeVisible(curr_y+1, curr_x);
                        q.push(std::make_pair(curr_y+1, curr_x));
                    }
                }
                
                //corners
                if(curr_x > 0 && curr_y > 0){
                    if(visible[curr_y-1][curr_x-1] == invisible){
                        makeVisible(curr_y-1, curr_x-1);
                        q.push(std::make_pair(curr_y-1, curr_x-1));
                    }
                }
                if(curr_x < size-1 && curr_y > 0){
                    if(visible[curr_y-1][curr_x+1] == invisible){
                        makeVisible(curr_y-1, curr_x+1);
                        q.push(std::make_pair(curr_y-1, curr_x+1));
                    }
                }
                if(curr_x < size-1 && curr_y < size-1){
                    if(visible[curr_y+1][curr_x+1] == invisible){
                        makeVisible(curr_y+1, curr_x+1);
                        q.push(std::make_pair(curr_y+1, curr_x+1));
                    }
                }
                if(curr_x > 0 && curr_y < size-1){
                    if(visible[curr_y+1][curr_x-1] == invisible){
                        makeVisible(curr_y+1, curr_x-1);
                        q.push(std::make_pair(curr_y+1, curr_x-1));
                    }
                }
                
            }

        }
    }
    
}

void MineSweeper::flag(int i, int j){
    
    if(i < 0 || i >= size || j < 0 || j >= size){
        std::cout << "Wrong input" << std::endl;
        return;
    }
    
    if(visible[i][j] != invisible && visible[i][j] != flagged){
        std::cout << "Nothing to flag" << std::endl;
        return;
    }
    
    if(visible[i][j] == flagged){ //can question here
        visible[i][j] = invisible;
        flaggedCount--;
    }
    else{
        visible[i][j] = flagged;
        flaggedCount++;
    }
    
}

int MineSweeper::getVisible(int i, int j){ //use .. for this
    if(visible[i][j] == invisible){
        return 0;
    }
    else if(visible[i][j] == flagged){
        return 1;
    }
    else if(visible[i][j] == 'X'){
        return 12;
    }
    return visible[i][j] - '0' + 3;
    
}

bool MineSweeper::isGameOver(){
    return !game;
}

bool MineSweeper::isGameWon(){
    if(uncoveredcells == size*size - mineCount){
        return true;
    }
    return false;
}

MineSweeper::~MineSweeper(){
    for(int i = 0; i < size; i++){
        delete board[i];
        delete visible[i];
    }
    delete board; //Creates board
    delete visible;
}




//TO DO
//flag or question mark placing
//having a counter of mines
//timer?

//when game over - make everything visible -- including flagged
//ADD empty opened cell
//Generate a random minesweeper board
