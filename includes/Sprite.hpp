#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE


#include "SDL_include.h"
#include <string>

class Sprite {

    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width;
        int height;

    public:
        Sprite();
        Sprite(std::string);
        ~Sprite();
        void Open(std::string);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
};
#endif 