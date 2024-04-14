//
//  main.m
//  SDL2_minesweeper
//
//  Created by Student on 8.04.2024.
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "minesweeper.h"
#include "engine.hpp"

int x = 50, y = 50;

int main(int argc, const char * argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        std::cout << "Error: " << IMG_GetError() << std::endl;
        return 1;
    }
    
    int windowHeight = 700, windowWidth = 980;
    SDL_Window * window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    
    if(!window){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        std::cout << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Event event;
    bool quit = false;
    
    
    GameEngine engine(renderer, windowHeight, windowWidth);

    int size = 20, mineCount = 40, factor = (windowHeight-150) / size;
    MineSweeper minesweeper = MineSweeper();
    minesweeper.generateBoard(size, mineCount);
    int rightShift = 200, downShift = 100;
    
    engine.init(size, factor, rightShift, downShift);
    engine.start_timer();
    factor++;
    while(!quit){//Event handling
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            //else handle event
            else if(engine.isGame()){
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&x, &y);
                    if(engine.isRestartClicked(x, y)){
                        engine.loadScreen();
                    }

                    else{
                        y-= downShift;
                        x-= rightShift;
                        if(y < 0 || x < 0 || minesweeper.isGameWon() || minesweeper.isGameOver()){ //to catch invalid moves
                        }
                        else if(event.button.button == SDL_BUTTON_LEFT){
                            minesweeper.play(y/factor,x/factor);
                        }
                        else if(event.button.button == SDL_BUTTON_RIGHT){
                            minesweeper.flag(y/factor,x/factor);
                        }
                    }
                }
            }
            else if(engine.isStart()){
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&x, &y);
                    
                    //NEW GAME
                    if(engine.isNewGameClicked(x,y)){
                        engine.loadScreen();
                    }
                    else if(engine.isQuitClicked(x, y)){
                        quit = true;
                    }
                    
                    //TO DO
                    //QUIT
                }
            }
            else if(engine.isLoad()){
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&x, &y);

                    if(engine.isEasyClicked(x,y)){
                        size = 10;
                        mineCount = 10;
                        factor = (windowHeight-150) / size;
                        
                        minesweeper.destroyBoard();
                        minesweeper.generateBoard(size, mineCount);

                        engine.init(size, factor, rightShift, downShift);
                        engine.start_timer();
                        factor++;
                        
                        engine.start_game();
                    }
                    else if(engine.isMediumClicked(x,y)){
                        size = 20;
                        mineCount = 40;
                        factor = (windowHeight-150) / size;
                        
                        minesweeper.destroyBoard();
                        minesweeper.generateBoard(size, mineCount);

                        
                        engine.init(size, factor, rightShift, downShift);
                        engine.start_timer();
                        factor++;
                        
                        engine.start_game();
                    }
                    else if(engine.isHardClicked(x,y)){
                        size = 40;
                        mineCount = 200;
                        factor = (windowHeight-150) / size;
                        
                        minesweeper.destroyBoard();
                        minesweeper.generateBoard(size, mineCount);
                        
                        engine.init(size, factor, rightShift, downShift);
                        engine.start_timer();
                        factor++;
                        
                        engine.start_game();
                    }
                    else if(engine.isCustomClicked(x, y)){
                        engine.customScreen();
                        
                    }
                    else if(engine.isQuitClicked(x, y)){
                        quit = true;
                    }
                    
                }
            }
            else if(engine.isCustom()){
                if(event.type == SDL_MOUSEBUTTONDOWN){
                    SDL_GetMouseState(&x, &y);

                    if(engine.isBackClicked(x,y)){
                        engine.loadScreen();
                    }
                    else if(true){
                        
                    }
                }
                
            }
            
            
        }
        
        if(!minesweeper.isGameWon() && !minesweeper.isGameOver()){
            engine.stop_timer();
        }
        
        engine.render(minesweeper);
        SDL_RenderPresent(renderer);
        
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
