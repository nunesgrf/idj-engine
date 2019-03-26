#include "Sound.hpp"

#define FIRST_FREE_CHANNEL -1
#define UNINITIALIZED -1

#include "Resources.hpp"
#include <iostream>

Sound::Sound(GameObject& associated): Component(associated), channel(UNINITIALIZED), chunk(nullptr) {}

Sound::Sound(GameObject& associated, std::string file): Sound(associated) {
    Open(file);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(FIRST_FREE_CHANNEL,chunk,times);
}

void Sound::Stop() {
    if((chunk != nullptr) and (channel = UNINITIALIZED))  {
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(std::string file) {
    chunk = Resources::GetSound(file); 
}

Sound::~Sound() {
}

void Sound::Update(float dt) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == std::string("Sound");
}