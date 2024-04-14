//
//  engine.cpp
//  SDL2_minesweeper
//
//  Created by Student on 9.04.2024.
//

#include "engine.hpp"


GameEngine::GameEngine(SDL_Renderer * renderer, int windowHeight, int windowWidth):renderer(renderer), windowHeight(windowHeight), windowWidth(windowWidth){
    boardimages = IMG_LoadTexture(renderer, "minesweeperart.png");
    timerimages = IMG_LoadTexture(renderer, "numbers.png");
    promptimages = IMG_LoadTexture(renderer, "minesweeperprompts.png");
    
    state = START;
    numbertexture = std::vector<SDL_Rect> (5); //positions of clock numbers
    int clock_x = 10, clock_y = 5;
    int numbersize = 40;
    for(int i = 0; i < numbertexture.size(); i++){
        numbertexture[i].x = clock_x;
        numbertexture[i].y = clock_y;
        numbertexture[i].w = numbersize;
        numbertexture[i].h = numbersize;
        clock_x+= numbersize+1;
    }
    
    numberpos = std::vector<SDL_Rect> (11); //textures of clock numbers
    int k = 0;
    for(int i = 0; i < 11; i++){
        numberpos[i].x = k;
        numberpos[i].y = 0;
        numberpos[i].w = 5;
        numberpos[i].h = 7;
        k += 5;
    }
    
    prompttexture = std::vector<SDL_Rect> (13);
    promptpos = std::vector<SDL_Rect> (13);
    
    std::vector<int> lengths = {29, 17, 28, 17, 49, 39, 30, 38, 29, 19, 17, 18, 18};
    k = 0;
    for(int i = 0; i < promptpos.size(); i++){
        promptpos[i].x = 0;
        promptpos[i].y = k;
        promptpos[i].w = lengths[i];
        promptpos[i].h = 9;
        k+= 9;
    }
    
    int textSize = 6;
    //Minesweeper
    prompttexture[MINESWEEPER].x = (windowWidth - lengths[MINESWEEPER]*textSize) / 2;
    prompttexture[MINESWEEPER].y = 120;
    prompttexture[MINESWEEPER].w = lengths[MINESWEEPER]*textSize;
    prompttexture[MINESWEEPER].h = 9*textSize;
    
    //GameOver
    prompttexture[GAMEOVER].x = 370;
    prompttexture[GAMEOVER].y = 30;
    prompttexture[GAMEOVER].w = lengths[GAMEOVER]*textSize;
    prompttexture[GAMEOVER].h = 9*textSize;
    
    //YOUWIN
    prompttexture[YOUWIN].x = 340;
    prompttexture[YOUWIN].y = 30;
    prompttexture[YOUWIN].w = lengths[YOUWIN]*textSize;
    prompttexture[YOUWIN].h = 9*textSize;
    
    //NEW GAME
    prompttexture[NEWGAME].x = (windowWidth - lengths[NEWGAME]*textSize) / 2;
    prompttexture[NEWGAME].y = 400;
    prompttexture[NEWGAME].w = lengths[NEWGAME]*textSize;
    prompttexture[NEWGAME].h = 9*textSize;
    
    //EASY
    prompttexture[EASY].x = (windowWidth - lengths[EASY]*textSize) / 2;
    prompttexture[EASY].y = 250;
    prompttexture[EASY].w = lengths[EASY]*textSize;
    prompttexture[EASY].h = 9*textSize;
    
    //MEDIUM
    prompttexture[MEDIUM].x = (windowWidth - lengths[MEDIUM]*textSize) / 2;
    prompttexture[MEDIUM].y = 310;
    prompttexture[MEDIUM].w = lengths[MEDIUM]*textSize;
    prompttexture[MEDIUM].h = 9*textSize;
    
    //HARD
    prompttexture[HARD].x = (windowWidth - lengths[HARD]*textSize) / 2;
    prompttexture[HARD].y = 370;
    prompttexture[HARD].w = lengths[HARD]*textSize;
    prompttexture[HARD].h = 9*textSize;
    
    //CUSTOM
    prompttexture[CUSTOM].x = (windowWidth - lengths[CUSTOM]*textSize) / 2;
    prompttexture[CUSTOM].y = 430;
    prompttexture[CUSTOM].w = lengths[CUSTOM]*textSize;
    prompttexture[CUSTOM].h = 9*textSize;
    
    //RESTART
    prompttexture[RESTART].x = windowWidth - lengths[RESTART]*textSize-20;
    prompttexture[RESTART].y = 600;
    prompttexture[RESTART].w = lengths[RESTART]*textSize;
    prompttexture[RESTART].h = 9*textSize;
    
    //QUIT
    prompttexture[QUIT].x = 20;
    prompttexture[QUIT].y = 600;
    prompttexture[QUIT].w = lengths[QUIT]*textSize;
    prompttexture[QUIT].h = 9*textSize;
    
    //BACK
    prompttexture[BACK].x = 20;
    prompttexture[BACK].y = 50;
    prompttexture[BACK].w = lengths[BACK]*textSize;
    prompttexture[BACK].h = 9*textSize;
    
    //SIZE
    prompttexture[SIZE].x = (windowWidth - lengths[SIZE]*textSize-200) / 2;
    prompttexture[SIZE].y = 250;
    prompttexture[SIZE].w = lengths[SIZE]*textSize;
    prompttexture[SIZE].h = 9*textSize;
    
    //MINE
    prompttexture[MINE].x = (windowWidth - lengths[MINE]*textSize-200) / 2;
    prompttexture[MINE].y = 350;
    prompttexture[MINE].w = lengths[MINE]*textSize;
    prompttexture[MINE].h = 9*textSize;
    
    arrowtexture.x = 51;
    arrowtexture.y = 88;
    arrowtexture.w = 9;
    arrowtexture.h = 12;
    
    arrowpos1.x = (windowWidth - 400);
    arrowpos1.y = 230;
    arrowpos1.w = 9*textSize;
    arrowpos1.h = 12*textSize;

    
    arrowpos2.x = (windowWidth - 400);
    arrowpos2.y = 340;
    arrowpos2.w = 9*textSize;
    arrowpos2.h = 12*textSize;
    
    
    
    counterpos = std::vector<SDL_Rect> (3);
    clock_x = 830;
    for(int i = 0; i < 3; i++){
        counterpos[i].x = clock_x;
        counterpos[i].y = clock_y;
        counterpos[i].w = numbersize;
        counterpos[i].h = numbersize;
        
        clock_x+= numbersize+1;
    }
}


void GameEngine::init(int size, int factor, int rightShift, int downShift){
    boardSize = size;
    
    

    tilepos = std::vector<SDL_Rect> (boardSize*boardSize); //textures of tiles
    
    int idx = 0, a = rightShift, b = downShift;
    for(int i = 0; i < boardSize; i++){
        a = rightShift;
        for(int j = 0; j < boardSize; j++){
            tilepos[idx].x = a;
            tilepos[idx].y = b;
            tilepos[idx].w = factor;
            tilepos[idx].h = factor;
            idx++;
            a+= factor + 1;
        }
        b+= factor+1;

    }
    factor++;
    
    
    tiletexture = std::vector<SDL_Rect> (13); //textures of tiles
    int k = 0;
    for(int i = 0; i < 13; i++){
        tiletexture[i].x = k;
        tiletexture[i].y = 0;
        tiletexture[i].w = 11;
        tiletexture[i].h = 11;
        k += 12;
    }
    

}


void GameEngine::render(MineSweeper & minesweeper){
    SDL_RenderClear(renderer); //if prev is different

    if(state == START){
        renderStart();
    }
    else if(state == LOADING){
        renderLoading();
    }
    else if(state == CUSTOMGAME){
        renderCustom();
    }
    else if(state == GAME){
        if(minesweeper.isGameWon()){
            SDL_RenderCopy(renderer,promptimages, &promptpos[YOUWIN], &prompttexture[YOUWIN]);
        }
        else if(minesweeper.isGameOver()){
            SDL_RenderCopy(renderer,promptimages, &promptpos[GAMEOVER], &prompttexture[GAMEOVER]);
        }
        renderGame(minesweeper);

    }
    
}

void GameEngine::renderGame(MineSweeper & minesweeper){
    //render the board
    int idx = 0;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            SDL_RenderCopy(renderer, boardimages, &tiletexture[minesweeper.getVisible(i,j)], &tilepos[idx]);
            idx++;
        }
    }
    
    time = timer();
    int min10 = (time / 60) / 10;
    int min1 = (time / 60) - min10*10;
    int sec10 = (time % 60)/ 10;
    int sec1 = (time % 60) - sec10*10;
    
    //render the timer
    SDL_RenderCopy(renderer,timerimages, &numberpos[min10], &numbertexture[0]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[min1], &numbertexture[1]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[10], &numbertexture[2]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[sec10], &numbertexture[3]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[sec1], &numbertexture[4]);
    
    //render the counter
    int mines = minesweeper.mineCount - minesweeper.flaggedCount;
    if(mines < 0){
        mines = 0;
    }
    int mines100 = mines / 100;
    int mines10 = (mines % 100) / 10;
    int mine1 = (mines % 10);
    
    SDL_RenderCopy(renderer, timerimages, &numberpos[mines100], &counterpos[0]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[mines10], &counterpos[1]);
    SDL_RenderCopy(renderer,timerimages, &numberpos[mine1], &counterpos[2]);
    
    SDL_RenderCopy(renderer,promptimages, &promptpos[RESTART], &prompttexture[RESTART]);

}

void GameEngine::renderStart(){
    SDL_RenderCopy(renderer,promptimages, &promptpos[MINESWEEPER], &prompttexture[MINESWEEPER]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[NEWGAME], &prompttexture[NEWGAME]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[QUIT], &prompttexture[QUIT]);

    //QUIT
    
    
}

void GameEngine::renderLoading(){
    SDL_RenderCopy(renderer,promptimages, &promptpos[MINESWEEPER], &prompttexture[MINESWEEPER]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[EASY], &prompttexture[EASY]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[MEDIUM], &prompttexture[MEDIUM]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[HARD], &prompttexture[HARD]);
    //SDL_RenderCopy(renderer,promptimages, &promptpos[CUSTOM], &prompttexture[CUSTOM]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[QUIT], &prompttexture[QUIT]);

}

void GameEngine::renderCustom(){
    //CUSTOM
    //MINE
    //SIZE
    //NEW GAME

    SDL_RenderCopy(renderer,promptimages, &promptpos[BACK], &prompttexture[BACK]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[SIZE], &prompttexture[SIZE]);
    SDL_RenderCopy(renderer,promptimages, &promptpos[MINE], &prompttexture[MINE]);

    SDL_RenderCopy(renderer,promptimages, &arrowtexture, &arrowpos1);
    SDL_RenderCopy(renderer,promptimages, &arrowtexture, &arrowpos2);

    
}


int GameEngine::timer(){
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(game_now-game_start);

    return time_span.count();
}

void GameEngine::start_timer(){
    game_start = std::chrono::high_resolution_clock::now();
}

void GameEngine::stop_timer(){
    game_now = std::chrono::high_resolution_clock::now();
}

GameEngine::~GameEngine(){
    SDL_DestroyTexture(boardimages);
    SDL_DestroyTexture(timerimages);
    SDL_DestroyTexture(promptimages);

    
}


bool GameEngine::isStart(){
    return state == START;
}
bool GameEngine::isLoad(){
    return state == LOADING;
}
bool GameEngine::isCustom(){
    return state == CUSTOMGAME;
}
bool GameEngine::isGame(){
    return state == GAME;
}


bool GameEngine::isClicked(int x, int y, int state){
    if(x > prompttexture[state].x && x < prompttexture[state].x + prompttexture[state].w
       && y > prompttexture[state].y && y <prompttexture[state].y + prompttexture[state].h){
        return true;
    }
    return false;
}


bool GameEngine::isNewGameClicked(int x, int y){
    return isClicked(x,y,NEWGAME);
}

bool GameEngine::isEasyClicked(int x, int y){
    return isClicked(x,y,EASY);
}
bool GameEngine::isMediumClicked(int x, int y){
    return isClicked(x,y,MEDIUM);
}
bool GameEngine::isHardClicked(int x, int y){
    return isClicked(x,y,HARD);
}
bool GameEngine::isCustomClicked(int x, int y){
    return isClicked(x,y,CUSTOM);
}

bool GameEngine::isRestartClicked(int x, int y){
    return isClicked(x,y,RESTART);
}

bool GameEngine::isQuitClicked(int x, int y){
    return isClicked(x,y,QUIT);
}

bool GameEngine::isBackClicked(int x, int y){
    return isClicked(x,y,BACK);
}

void GameEngine::loadScreen(){
    state = LOADING;
}

void GameEngine::start_game(){
    state = GAME;
}

void GameEngine::startScreen(){
    state = START;
}

void GameEngine::customScreen(){
    state = CUSTOMGAME;
}
