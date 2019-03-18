#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include <iostream>

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {
}

Sprite::Sprite(GameObject& associated, std::string file): Component(associated), texture(nullptr) {
    
    this->texture = nullptr;
    this->Open(file);
}

Sprite::~Sprite() {
    if(this->texture != nullptr) SDL_DestroyTexture(this->texture);
}

void Sprite::Open(std::string file) {
    Game * aux = &Game::GetInstance();

    if(this->texture != nullptr) SDL_DestroyTexture(this->texture);
    this->texture = IMG_LoadTexture(aux->GetRenderer(),file.c_str());

    if(this->texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(-2);
    }

    SDL_QueryTexture(this->texture,nullptr,nullptr,&this->width,&this->height);

    this->SetClip(0,0,this->width,this->height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    this->clipRect.x = x;
    this->clipRect.y = y;
    this->clipRect.w = w;
    this->clipRect.h = h;
}

void Sprite::Render() {

}

void Sprite::Render(int x, int y) {
    SDL_Rect dstrect;
    Game * aux = &Game::GetInstance();

    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = this->clipRect.w;
    dstrect.h = this->clipRect.h;

    SDL_RenderCopy(aux->GetRenderer(),this->texture,&this->clipRect,&dstrect);
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}

bool Sprite::IsOpen() {
    return this->texture != nullptr;
}

bool Sprite::Is(std::string type) {
    return type == "Sprite";
}

void Sprite::Update(float dt) {
}
