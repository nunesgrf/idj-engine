#ifndef GAME_H
#define GAME_H

#define WINDOW      SDL_Window
#define RENDERER    SDL_Renderer

#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.hpp"
#include <string>

class Game {
    
    private:  
        WINDOW* window;
        RENDERER* renderer;
        State* state;
        static Game* instance;
        Game(std::string title, int width, int height);

    public: 
        RENDERER* GetRenderer();
        State& GetState();
        static Game& GetInstance();
        void Run(); 
        ~Game();   
};
#endif 