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
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

    public:
        Sprite(GameObject&);
        Sprite(GameObject&,std::string, int frameCount = 1, float frameTime = 1);
        ~Sprite();
        void Start();
        void Open(std::string);
        void SetClip(int,int,int,int);
        void Render();
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        bool Is(std::string);
        void Update(float);
        Vec2 GetScale();
        void SetScale(float scaleX, float scaleY);
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
};
#endif 