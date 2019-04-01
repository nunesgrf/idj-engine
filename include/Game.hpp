#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL

#define DEFAULT_NAME "Gabriel Nunes - 16/0006597"
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 600

#include "SDL_include.h"
#include "State.hpp"
#include <string>

class Game {
    
    private:
        static Game* instance;
        SDL_Window*  window;
        SDL_Renderer* renderer;
        State* state;
        int frameStart;
        float dt;
        int width;
        int height;
        void CalculateDeltaTime();
        Game(std::string name = DEFAULT_NAME, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT);

    public:
        int GetWidth();
        int GetHeight();
        float GetDeltaTime();
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetState();
        void Run();
        ~Game();
};
#endif 