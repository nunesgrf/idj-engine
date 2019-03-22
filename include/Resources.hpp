#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include <unordered_map>
#include <string>

class Resources {
    private:
        static std::unordered_map<std::string,Mix_Chunk*> soundTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, SDL_Texture*> imageTable;

    public:
        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();

        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();

        static SDL_Texture* GetImage(std::string file);
        static void ClearImages();
};
#endif