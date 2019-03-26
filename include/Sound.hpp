#ifndef SOUND_H
#define SOUND_H

#define MIX_CHUNK Mix_Chunk
#define ONE_REPEAT 1
#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Sound : public Component {
    private:
        MIX_CHUNK* chunk;
        int channel;
    
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated,std::string file);
        ~Sound();
        void Play(int loops = ONE_REPEAT);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(std::string type); // Is this right?
};
#endif 