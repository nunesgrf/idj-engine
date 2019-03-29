#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
#include <iostream>

#define START_X 0
#define START_Y 0
#define ERROR_SPRITE -222

Sprite::Sprite(): texture(nullptr) {}

Sprite::Sprite(std::string file): Sprite() {
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

void Sprite::Render(int x, int y) {
    RECT dstrect;
    Game &game = Game::GetInstance();

    dstrect = {x,y,clipRect.w,clipRect.h};
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