#include "../include/Sound.hpp"

#include "../include/Resources.hpp"

Sound::Sound(GameObject& associated): Component(associated), channel(-1) {
    this->chunk = nullptr;  
}

Sound::Sound(GameObject& associated, std::string file): Component(associated), channel(-1), chunk(nullptr) {
    this->Open(file);
}

void Sound::Play(int times) {
    this->channel = Mix_PlayChannel(-1,this->chunk,times);
}

void Sound::Stop() {
    if(this->chunk != nullptr) Mix_HaltChannel(this->channel);
}

void Sound::Open(std::string file) {
    this->chunk = Resources::GetSound(file); 
}

Sound::~Sound() {
    if(this->channel != -1) {
        Mix_HaltChannel(this->channel);
    }
}

void Sound::Update(float dt) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == std::string("Sound");
}