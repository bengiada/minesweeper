//
//  engine.hpp
//  SDL2_minesweeper
//
//  Created by Student on 9.04.2024.
//

#ifndef engine_hpp
#define engine_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <vector>
#include "minesweeper.h"
#include <chrono>



class GameEngine{
public:
    GameEngine(SDL_Renderer * renderer, int windowheight, int windowwidth);
    
    void init(int,int,int,int);
    void render(MineSweeper &);
    void start_timer();
    void stop_timer();
    //void handle_event();
    
    bool isStart();
    bool isLoad();
    bool isCustom();
    bool isGame();
    
    bool isNewGameClicked(int, int);
    bool isEasyClicked(int, int);
    bool isMediumClicked(int, int);
    bool isHardClicked(int, int);
    bool isCustomClicked(int, int);
    bool isRestartClicked(int, int);
    bool isQuitClicked(int, int);
    bool isBackClicked(int, int);


    void start_game();
    
    void loadScreen();
    void startScreen();
    void customScreen();
    
    ~GameEngine();
    
private:
    int windowHeight, windowWidth;
    int boardSize;
    int time;
    
    std::chrono::high_resolution_clock::time_point game_now;
    std::chrono::high_resolution_clock::time_point game_start;
    
    SDL_Renderer * renderer;
    SDL_Texture * boardimages;
    SDL_Texture * timerimages;
    SDL_Texture * promptimages;

    
    std::vector<SDL_Rect> tiletexture;
    std::vector<SDL_Rect> tilepos;
    
    std::vector<SDL_Rect> numbertexture;
    std::vector<SDL_Rect> numberpos;

    std::vector<SDL_Rect> prompttexture;
    std::vector<SDL_Rect> promptpos;

    std::vector<SDL_Rect> counterpos;
    
    SDL_Rect arrowtexture;
    SDL_Rect arrowpos1;
    SDL_Rect arrowpos2;


    
    enum prompts {RESTART, EASY, MEDIUM, HARD, MINESWEEPER, GAMEOVER, YOUWIN, NEWGAME, CUSTOM, MINE, SIZE, QUIT, BACK};
    enum states {START, LOADING, CUSTOMGAME, GAME};
    int state;

    
    int timer();
    void renderGame(MineSweeper &);
    void renderLoading();
    void renderCustom();
    void renderStart();

    bool isClicked(int, int, int);
    
};

#endif /* engine_hpp */
