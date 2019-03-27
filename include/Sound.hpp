#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER

#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Sound : public Component {
    private:
        Mix_Chunk* chunk;
        int channel;
    
    public:
        Sound(GameObject&);
        Sound(GameObject&,std::string);
        ~Sound();
        void Start();
        void Play(int = 1);
        void Stop();
        void Open(std::string);
        bool IsOpen();
        void Update(float);
        void Render();
        bool Is(std::string); // Is this right?
};
#endif 