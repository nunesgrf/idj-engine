#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER

#define DEFAULT_FADEOUT 0
#define INFINITE_REPEATS -1

#include "SDL_include.h"
#include <string>
#include <memory>

class Music {
    private:
        std::shared_ptr<Mix_Music> music;

    public:
        Music();
        Music(std::string);
        ~Music();
        void Play(int repeates =  INFINITE_REPEATS);
        void Stop(int fadeout = DEFAULT_FADEOUT);
        void Open(std::string);
        bool IsOpen();

};

#endif 