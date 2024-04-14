//
//  minesweeper.h
//  SDL2_minesweeper
//
//  Created by Student on 10.04.2024.
//

#ifndef minesweeper_h
#define minesweeper_h

class MineSweeper{
public:

    MineSweeper(){
        game = true;
        uncoveredcells = 0;
        flaggedCount = 0;
    }
    
    void printBoard();
    void startGame();
    int getVisible(int, int);
    void play(int, int);
    void flag(int, int);
    bool isGameOver();
    bool isGameWon();
    int mineCount;
    int flaggedCount;
    void generateBoard(int, int);
    void destroyBoard();
    ~MineSweeper();
    
private:
    int size;
    char ** board;
    char ** visible;
    static const char invisible = '-';
    static const char flagged = 'F';
    bool game;
    int uncoveredcells;
    
    
    void updateCell(int,int); //Used when generating board - updates numbers
    void makeVisible(int,int);
    void makeEverythingVisible();
    
};


#endif /* minesweeper_h */
