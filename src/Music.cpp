#include "../includes/Music.hpp"

#include <iostream>

Music::Music() {
    this->music = nullptr;
}

Music::Music(std::string file) {
    this->music = nullptr;
    this->Open(file);
}

void Music::Play(int times) {
    if(this->music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-30);
    }
    Mix_PlayMusic(this->music, times);
}

void Music::Stop(int msToStop) {
    if(this->music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-31);
    }
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    this->music = Mix_LoadMUS(file.c_str());

    if(this->music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-32);
    }
}

bool Music::IsOpen() {
    return this->music != nullptr;
}

Music::~Music() {
    if(this->music != nullptr) {
        this->Stop();
        Mix_FreeMusic(this->music);
    }
}