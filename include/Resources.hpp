#ifndef RESOURCES_H
#define RESOURCES_H

#define MIX_CHUNK Mix_Chunk

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <unordered_map>
#include <string>

class Resources {
    private:
        static std::unordered_map<std::string,MIX_CHUNK*> soundTable;

    public:
        static MIX_CHUNK* GetSound(std::string file);
        static void ClearSounds();
};
#endif