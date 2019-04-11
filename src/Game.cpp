#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#include "../include/SDL_include.h"
#include "../include/Game.hpp"
#include "../include/InputManager.hpp"
#include "Resources.hpp"
#include <iostream>

Game* Game::instance;

Game::Game(std::string title, int width, int height): dt(0), frameStart(0), width(width), height(height), storedState(nullptr) {
    if(this->instance == nullptr) {
        this->instance = this;
        
        if(TTF_Init() != 0) {
            std::cout << "TTF_Init_ERROR: " << SDL_GetError() << std::endl;
        }
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
    return *stateStack.top();
}

void Game::Push(State* state) {
    storedState = state;
}

SDL_Renderer* Game::GetRenderer() {
    return this->renderer;
}

void Game::Run() {
    if(not storedState) {
        std::cout << "FATAL ERROR: impossible to initialize a game instance" << std::endl;
        exit(-1);
    }
    stateStack.emplace(storedState);
    storedState = nullptr;

    GetState().Start();

    while(not stateStack.empty() and not GetState().QuitRequested()){
        State* state = &GetState();

        if(state->PopRequested()) {
            stateStack.pop();
            Resources::Clear();
            if(not stateStack.empty()) {
                state = &GetState();
                state->Resume();
            }
        }

        if(storedState) {
            if(not stateStack.empty()) {
                state->Pause();
            }
            stateStack.emplace(storedState);
            state = &GetState();
            state->Start();
            storedState = nullptr;
        }

        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);

        
    }
    
    while(stateStack.size() > 1) {
        stateStack.pop();
    }
    Resources::Clear();
    
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
    if(storedState != nullptr) {
        delete this->storedState;
    }
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
}


