#include "Sound.hpp"

#include "Resources.hpp"
#include <iostream>

Sound::Sound(GameObject& associated): Component(associated), channel(-1), chunk(nullptr) {}

Sound::Sound(GameObject& associated, std::string file): Sound(associated) {
    Open(file);
}

void Sound::Play(int times) {
    channel = Mix_PlayChannel(-1,chunk.get(),times);
}

void Sound::Stop() {
    if((chunk.get() != nullptr) and (channel = -1))  {
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

void Sound::Start() {}