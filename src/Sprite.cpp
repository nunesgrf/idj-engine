#include "Sprite.hpp"

#include "Camera.hpp"
#include "Resources.hpp"
#include "Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated, int frameCount, float frameTime, float stsd): Component(associated), texture(nullptr), scale({1,1}), frameCount(frameCount), frameTime(frameTime), timeElapsed(0), currentFrame(0), secondToSelfDestruct(stsd) {}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float stsd): Sprite(associated, frameCount, frameTime,stsd) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    if(texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(texture.get(),nullptr,nullptr,&width,&height);
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    SetClip(currentFrame,0,GetWidth(),GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    Game &aux = Game::GetInstance();

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w*scale.x;
    dstrect.h = clipRect.h*scale.y;
    SDL_RenderCopyEx(aux.GetRenderer(),texture.get(),&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
}

void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x,associated.box.y-Camera::pos.y);
}

void Sprite::Start() {
    
}
int Sprite::GetWidth() {
    return (scale.x*width)/frameCount;
}

int Sprite::GetHeight() {
    return height*scale.y;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

bool Sprite::Is(std::string type) {
    return type == std::string("Sprite");
}

void Sprite::SetScale(float scaleX, float scaleY) {
    if(scale.x <= 0) scaleX = scale.x;
    if(scale.y <= 0) scaleY = scale.y;

    associated.box.x = associated.box.Center().x - associated.box.CenterOffset().x;
    associated.box.y = associated.box.Center().y - associated.box.CenterOffset().y;

    associated.box.w = GetWidth();
    associated.box.h = GetHeight();

    scale = {scaleX,scaleY};
}

Vec2 Sprite::GetScale() {
    return scale;
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    if(timeElapsed > frameTime) {
        currentFrame++;
        SetFrame(currentFrame);
        timeElapsed = 0;
    }

    if(secondToSelfDestruct > 0) {
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() >= secondToSelfDestruct) associated.RequestDelete();
    }
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame < frameCount? frame : 0;
    SetClip(currentFrame*width/frameCount,0, width/frameCount, clipRect.h);
    
}

void Sprite::SetFrameCount(int frameCount) {
    Sprite::frameCount = frameCount;
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    SetClip(0, clipRect.y, GetWidth(),clipRect.h);
}

void Sprite::SetFrameTime(float frameTime) {
    Sprite::frameTime = frameTime;
}
