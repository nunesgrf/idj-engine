#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#define ERROR_GAME -111
#define NO_DT 0
#define WIDTH 1024
#define HEIGHT 600
#define ALLOCATED_CHANNELS 32
#define DEFAULT_DELAY 33
#define BEST_RENDERER -1
#define NAME "Gabriel Nunes - 16/0006597"

#include "SDL_include.h"
#include "Game.hpp"
#include <iostream>

Game* Game::instance;

Game::Game(std::string title, int width, int height) {
    if(instance == nullptr) {
        instance = this;   
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            std::cout << "SDL_Init_ERROR: " <<  SDL_GetError() << std::endl;
            exit(ERROR_GAME);
        }
        if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
            std::cout << "IMG_Init_ERROR: " << SDL_GetError() << std::endl;
            exit(ERROR_GAME);
        }
        if(Mix_Init(MIX_INIT_OGG) == 0) {
            std::cout << "Mix_Init_ERROR: " << SDL_GetError() << std::endl;
            exit(ERROR_GAME);
        }
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0) {
            std::cout << "Mix_OpenAudio_ERROR: " << SDL_GetError() << std::endl;
            exit(ERROR_GAME);
        }
        Mix_AllocateChannels(ALLOCATED_CHANNELS);

        window   = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
        renderer = SDL_CreateRenderer(window,BEST_RENDERER,SDL_RENDERER_SOFTWARE);
        if(window == nullptr || renderer == nullptr) {
            std::cout << "SDL_CreateWindow_Renderer_ERROR: " << SDL_GetError() << std::endl;
            exit(ERROR_GAME);
        }
        state = new State();
    }
    else {
        std::cout << "Nullpointer exception." << std::endl << "Impossible to initialize." << std::endl << "Execution aborted." << std::endl;
        exit(ERROR_GAME);
    }   
}

Game& Game::GetInstance() {
    if(instance == nullptr) new Game(NAME,WIDTH,HEIGHT);
    return *instance;
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::Run() {
    while(not state->QuitRequested()) {     
        state->Render();
        state->Update(NO_DT);
        SDL_RenderPresent(renderer);  
        SDL_Delay(DEFAULT_DELAY);
    } 
}

Game::~Game() {
    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


