#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.hpp"
#include <string>

class Game {
    
    private:
        static Game* instance;
        SDL_Window*  window;
        SDL_Renderer* renderer;
        State* state;
        Game(std::string, int width, int height);

    public:
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetState();
        void Run();
        ~Game();
};
#endif 