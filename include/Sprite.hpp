#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "GameObject.hpp"
#include "Component.hpp"
#include "SDL_include.h"
#include <string>

class Sprite : public Component {

    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width;
        int height;

    public:
        Sprite(GameObject&);
        Sprite(GameObject&,std::string);
        ~Sprite();
        void Open(std::string);
        void SetClip(int,int,int,int);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        bool Is(std::string);
        void Update(float);
};
#endif 