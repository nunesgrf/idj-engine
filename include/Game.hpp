#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL

#define DEFAULT_NAME "Gabriel Nunes - 16/0006597"
#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 600

#include "SDL_include.h"
#include "State.hpp"
#include <string>
#include <stack>

class Game {
    
    private:
        static Game* instance;
        SDL_Window*  window;
        SDL_Renderer* renderer;
        State* storedState;
        int frameStart;
        float dt;
        int width;
        int height;
        std::stack<std::unique_ptr<State>> stateStack;

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
        void Push(State* state);
        ~Game();
};
#endif 