#ifndef SPRITE_H
#define SPRITE_H

#define TEXTURE SDL_Texture
#define RECT SDL_Rect

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include <string>

class Sprite {

    private:
        TEXTURE* texture;
        RECT clipRect;
        int width;
        int height;

    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
};
#endif 