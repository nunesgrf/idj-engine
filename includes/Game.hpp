#define INCLUDE_SDL

#include "SDL_include.h"
#include <string>

class Game {
    
    Game * instance;
    Game(std::string title, int width, int height);

};