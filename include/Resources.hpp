#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <unordered_map>
#include <string>

class Resources {
    private:
        static std::unordered_map<std::string,Mix_Chunk*> soundTable;

    public:
        static Mix_Chunk* GetSound(std::string);
        static void ClearSounds();
};
#endif