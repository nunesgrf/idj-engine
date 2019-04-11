#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <unordered_map>
#include <memory>
#include <string>

class Resources {
    private:
        static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
        static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

    public:
        static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
        static void ClearSounds();

        static std::shared_ptr<Mix_Music> GetMusic(std::string file);
        static void ClearMusics();

        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        static void ClearImages();

        static std::shared_ptr<TTF_Font> GetFont(std::string file, int ptsize);
        static void ClearFonts();
};
#endif