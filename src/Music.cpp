#include "Music.hpp"

#include "Resources.hpp"
#include <iostream>

Music::Music(): music(nullptr) {}

Music::Music(std::string file): Music() {
    Open(file);
}

void Music::Play(int times) {
    if(music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-30);
    }
    Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop) {
    if(music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-31);
    }
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file) {
    //music = Mix_LoadMUS(file.c_str());
    music = Resources::GetMusic(file);
    if(music == nullptr) {
        std::cout << "NullPointer_Music_Error: " << SDL_GetError() << std::endl;
        exit(-32);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    /*if(music != nullptr) {
        Stop();
        Mix_FreeMusic(music);
    }*/
}