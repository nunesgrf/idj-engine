#include "../include/Sprite.hpp"

#include "Camera.hpp"
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {}

Sprite::Sprite(GameObject& associated, std::string file): Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(std::string file) {
    texture = Resources::GetImage(file);
    if(texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

    SetClip(0,0,width,height);
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
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;

    SDL_RenderCopy(aux->GetRenderer(),texture,&clipRect,&dstrect);
}

void Sprite::Render() {
    Render(associated.box.x-Camera::pos.x,associated.box.y-Camera::pos.y);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

bool Sprite::Is(std::string type) {
    return type == std::string("Sprite");
}

void Sprite::Update(float dt) {}
