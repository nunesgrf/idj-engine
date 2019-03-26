#include "Sprite.hpp"
#include "Game.hpp"
#include <iostream>

#define START_X 0
#define START_Y 0
#define ERROR_SPRITE -222

Sprite::Sprite(GameObject& associated): Component(associated), texture(nullptr) {}

Sprite::Sprite(GameObject& associated, std::string file): Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {
    if(texture != nullptr) SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file) {
    Game &game = Game::GetInstance();

    if(texture != nullptr) SDL_DestroyTexture(texture);
    texture = IMG_LoadTexture(game.GetRenderer(),file.c_str());

    if(texture == nullptr) {
        std::cout << "Nullpointer_Texture_ERROR: " << SDL_GetError() << std::endl;
        exit(ERROR_SPRITE);
    }

    SDL_QueryTexture(texture,nullptr,nullptr,&width,&height);

    SetClip(START_X,START_Y,width,height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect = {x,y,w,h};
}

void Sprite::Render() {
    RECT dstrect;
    Game &game = Game::GetInstance();

    dstrect ={(int)associated.box.x,(int)associated.box.y,clipRect.w,clipRect.h};
    SDL_RenderCopy(game.GetRenderer(),texture,&clipRect,&dstrect);
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

void Sprite::Update(float dt) {
}
