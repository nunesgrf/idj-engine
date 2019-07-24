#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#define NOT_SELF_DESTRUCTIBLE 0
#define DEFAULT 1

#include "GameObject.hpp"
#include "Component.hpp"
#include "SDL_include.h"
#include "Timer.hpp"
#include "Vec2.hpp"
#include <string>

class Sprite : public Component {

    private:
        std::shared_ptr<SDL_Texture> texture;
        SDL_Rect clipRect;
        int width;
        int height;
        int currentFrame;
        int frameCount;
        float frameTime;
        float timeElapsed;
        float secondToSelfDestruct;
        Timer selfDestructCount;
        Vec2 scale;

    public:
        Sprite(GameObject& associated, int frameCount = DEFAULT, float frameTime = DEFAULT, float secondToSelfDestruct = NOT_SELF_DESTRUCTIBLE);
        Sprite(GameObject& associated,std::string file,int frameCount = DEFAULT, float frameTime = DEFAULT, float secondToSelfDestruct = NOT_SELF_DESTRUCTIBLE);
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
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
};
#endif 