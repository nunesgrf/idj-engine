#ifndef MUSIC_H
#define MUSIC_H

#define INFINITE_REPEATS -1
#define FADEOUT_DEFAULT 1500
#define MIX_MUSIC Mix_Music

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include <string>

class Music {
    private:
        MIX_MUSIC* music;

    public:
        Music();
        Music(std::string file);
        ~Music();
        void Play(int times = INFINITE_REPEATS);
        void Stop(int msToStop= FADEOUT_DEFAULT);
        void Open(std::string file);
        bool IsOpen();
};

#endif 