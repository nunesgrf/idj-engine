#include "../include/Sprite.hpp"

#include "Camera.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime): Component(associated), texture(nullptr), frameCount(frameCount),frameTime(frameTime), timeElapsed(0), currentFrame(0) {
    
    this->texture = nullptr;
    this->Open(file);
    scale = Vec2(1,1);
}

Sprite::~Sprite() {
    //if(this->texture != nullptr) SDL_DestroyTexture(this->texture);
    // think about it
}

void Sprite::Open(std::string file) {
    //Game * aux = &Game::GetInstance();

    //if(this->texture != nullptr) SDL_DestroyTexture(this->texture);
    //this->texture = IMG_LoadTexture(aux->GetRenderer(),file.c_str());
    this->texture = Resources::GetImage(file);
    if(this->texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(this->texture,nullptr,nullptr,&this->width,&this->height);
    associated.box.w = width;
    associated.box.h = height;
    this->SetClip(currentFrame,0,this->width/frameCount,this->height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    Game * aux = &Game::GetInstance();

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = this->clipRect.w*scale.x;
    dstrect.h = this->clipRect.h*scale.y;

    SDL_RenderCopyEx(aux->GetRenderer(),this->texture,&this->clipRect,&dstrect,this->associated.angleDeg,nullptr,SDL_FLIP_NONE);
}

void Sprite::Render() {
    this->Render(this->associated.box.x-Camera::pos.x,this->associated.box.y-Camera::pos.y);
}

void Sprite::Start() {
    
}
int Sprite::GetWidth() {
    return (this->width*scale.x)/frameCount;
}

int Sprite::GetHeight() {
    return this->height*scale.y;
}

bool Sprite::IsOpen() {
    return this->texture != nullptr;
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
    if(frameTime >= 1.2) std::cout << timeElapsed << " " << frameTime << std::endl;
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
