#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER

#include "../include/SDL_include.h"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include <iostream>

Game* Game::instance;

Game::Game(std::string title, int width, int height): dt(0), frameStart(0), width(width), height(height) {
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
        this->state = new State();
    }
    else {
        std::cout << "Nullpointer exception." << std::endl << "Impossible to initialize." << std::endl << "Execution aborted." << std::endl;
        exit(-1);
    }   
}

Game& Game::GetInstance() {
    if(instance == nullptr) new Game("Gabriel Nunes - 16/0006597",1024,600);
    return *instance;
}

State& Game::GetState() {
    return *(this->state);
}

SDL_Renderer* Game::GetRenderer() {
    return this->renderer;
}

void Game::Run() {
    InputManager * inputManager = &InputManager::GetInstance();
    this->state->Start();

    while(!this->state->QuitRequested()) { 
        this->CalculateDeltaTime();    
        this->state->Render();
        inputManager->Update();
        this->state->Update(GetDeltaTime());
        SDL_RenderPresent(this->renderer);  
        //SDL_Delay(33);
    } 
}

float Game::GetDeltaTime() {
    return this->dt;
}

void Game::CalculateDeltaTime() {
    int time = SDL_GetTicks();
    this->dt = (time - this->frameStart)/1000.0f;
    this->frameStart = time;
}

int Game::GetHeight() {
    return this->height;
}

int Game::GetWidth() {
    return this->width;
}

Game::~Game() {
    delete this->state;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}


