#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "GameObject.hpp"
#include "Component.hpp"
#include "SDL_include.h"
#include "Vec2.hpp"
#include <string>

class Sprite : public Component {

    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width;
        int height;
        Vec2 scale;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated,std::string file);
        ~Sprite();
        void Start();
        void Open(std::string file);
        void SetClip(int x,int y,int w,int h);
        void Render();
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        bool Is(std::string type);
        void Update(float dt);
        Vec2 GetScale();
        void SetScale(float scaleX, float scaleY);
};
#endif 