#include "../include/Sprite.hpp"

#include "Camera.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime): Component(associated), texture(nullptr), frameCount(frameCount),frameTime(frameTime), timeElapsed(0), currentFrame(0) {
    Open(file);
    scale = Vec2(1,1);
}

Sprite::~Sprite() {
    //if(texture != nullptr) SDL_DestroyTexture(texture);
    // think about it
}

void Sprite::Open(std::string file) {
    //Game * aux = &Game::GetInstance();

    //if(texture != nullptr) SDL_DestroyTexture(texture);
    //texture = IMG_LoadTexture(aux->GetRenderer(),file.c_str());
    texture = Resources::GetImage(file);
    if(texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
    associated.box.w = GetWidth();
    associated.box.h = GetHeight();
    SetClip(0,0,width/frameCount,height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    Game * aux = &Game::GetInstance();

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = clipRect.w*scale.x;
    dstrect.h = clipRect.h*scale.y;

    SDL_RenderCopyEx(aux->GetRenderer(),texture,&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
}

void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x,associated.box.y-Camera::pos.y);
}

void Sprite::Start() {
    
}
int Sprite::GetWidth() {
    return (int)(width*scale.x)/frameCount;
}

int Sprite::GetHeight() {
    return (int)height*scale.y;
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

    //associated.box.w = width*scaleX;
    associated.box.x = associated.box.Center().x - associated.box.w/2;

    //associated.box.h = height*scaleY;
    associated.box.y = associated.box.Center().y - associated.box.x/2;

    scale = {scaleX,scaleY};
}

Vec2 Sprite::GetScale() {
    return scale;
}
void Sprite::Update(float dt) {
    timeElapsed += dt;
    if(timeElapsed >= frameTime) {
        if(++currentFrame >= frameCount) currentFrame = 0;
        SetFrame(currentFrame);
        timeElapsed = 0;
    }
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    SetClip(frame*GetWidth(), 0, clipRect.w, clipRect.h);
}
void Sprite::SetFrameCount(int framecount) {
    frameCount = framecount;
    associated.box.w = GetWidth();
    SetClip(0,clipRect.y,GetWidth(),clipRect.h);
  
}
void Sprite::SetFrameTime(float frametime) {
    frameTime = frametime;
}
