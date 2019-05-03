#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>

class Music {
    private:
        Mix_Music* music;

    public:
        Music();
        Music(std::string);
        ~Music();
        void Play(int repeats = -1);
        void Stop(int default_fade = 1500);
        void Open(std::string file);
        bool IsOpen(); 

};

#endif 