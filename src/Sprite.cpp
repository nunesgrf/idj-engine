#include "../include/Sprite.hpp"

#include "Camera.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {
}

Sprite::Sprite(GameObject& associated, std::string file): Sprite(associated) {
    Open(file);
    scale = Vec2(1,1);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    if(texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);
    associated.box.w = width;
    associated.box.h = height;
    SetClip(0,0,width,height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x,y,w,h};
}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    Game * aux = &Game::GetInstance();

    dstrect = {x, y, clipRect.w*scale.x, clipRect.h*scale.y};
    SDL_RenderCopyEx(aux->GetRenderer(),texture,&clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
}

void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x,associated.box.y-Camera::pos.y);
}

void Sprite::Start() {
    
}
int Sprite::GetWidth() {
    return width*scale.x;
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

    scale = {scaleX,scaleY};
}

Vec2 Sprite::GetScale() {
    return scale;
}
void Sprite::Update(float dt) {
}
