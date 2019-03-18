#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER

#include "../include/SDL_include.h"
#include <string>

class Music {
    private:
        Mix_Music* music;

    public:
        Music();
        Music(std::string);
        ~Music();
        void Play(int = -1);
        void Stop(int = 1500);
        void Open(std::string);
        bool IsOpen();

};

#endif 