#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER

#define ONE_REPEAT 1

#include "SDL_include.h"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>
#include <memory>

class Sound : public Component {
    private:
        std::shared_ptr<Mix_Chunk> chunk;
        int channel;
    
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated,std::string file);
        ~Sound();
        void Start();
        void Play(int = ONE_REPEAT);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        void Update(float dt);
        void Render();
        bool Is(std::string type); 
};
#endif 