#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "../includes/SDL_include.h"
#include "../includes/Game.hpp"
#include <iostream>

Game* Game::instance;

Game::Game(std::string title, uint32_t width, uint32_t height) {
    if(this->instance == nullptr) {
        this->instance = this;
        
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            std::cout << "SDL_Init_ERROR: " <<  SDL_GetError() << std::endl;
            exit(-1);
        }
        if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
            std::cout << "IMG_Init_ERROR: " << SDL_GetError() << std::endl;
            exit(-1);
        }
        if(Mix_Init(MIX_INIT_OGG) == 0) {
            std::cout << "Mix_Init_ERROR: " << SDL_GetError() << std::endl;
            exit(-1);
        }
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024) != 0) {
            std::cout << "Mix_OpenAudio_ERROR: " << SDL_GetError() << std::endl;
            exit(-1);
        }
        Mix_AllocateChannels(32);

        this->window   = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
        this->renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
        if(window == nullptr || renderer == nullptr) {
            std::cout << "SDL_CreateWindow_Renderer_ERROR: " << SDL_GetError() << std::endl;
            exit(-1);
        }
        getchar();
    }
    else {
        std::cout << "Nullpointer exception." << std::endl << "Impossible to initialize." << std::endl << "Execution aborted." << std::endl;
        exit(-1);
    }   
}

Game& Game::GetInstance() {
    if(instance == nullptr) Game * aux = new Game("Gabriel Nunes - 16/0006597",1024,600); 
    return *instance;
}

SDL_Renderer* Game::GetRenderer() {
    return this->renderer;
}

void Game::Run() {

}

Game::~Game() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


