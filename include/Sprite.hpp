#ifndef SPRITE_H
#define SPRITE_H

#define TEXTURE SDL_Texture
#define RECT SDL_Rect

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "GameObject.hpp"
#include "Component.hpp"
#include "SDL_include.h"
#include <string>

class Sprite : public Component {

    private:
        TEXTURE* texture;
        RECT clipRect;
        int width;
        int height;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated,std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x,int y,int w,int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        bool Is(std::string file);
        void Update(float dt);
};
#endif 