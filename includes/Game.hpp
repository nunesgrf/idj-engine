#ifndef GAME_H
#define GAME_H

#define INCLUDE_SDL

#include "SDL_include.h"
#include <string>

class Game {
    
    private:
        static Game* instance;
        SDL_Window*  window;
        SDL_Renderer* renderer;
        //State* state;
        Game(std::string, uint32_t, uint32_t);

    public:
        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        //State& GetState();
        void Run();
        ~Game();
};
#endif 