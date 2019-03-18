#include "../include/Sound.hpp"

Sound::Sound(GameObject& associated): Component(associated) {
    this->chunk = nullptr;  
}

Sound::Sound(GameObject& associated, std::string file): Component(associated) {
    this->Open(file);
}

void Sound::Play(int times) {
    this->channel = Mix_PlayChannel(-1,this->chunk,times);
}

void Sound::Stop() {
    if(this->chunk != nullptr) Mix_HaltChannel(this->channel);
}

void Sound::Open(std::string file) {
    try {
        Mix_LoadWAV(file.c_str());
    }
    catch(...) { 
        // think about what to do 
        this->chunk = nullptr;
    }
}

Sound::~Sound() {
    if(this->chunk != nullptr) {
        Mix_HaltChannel(this->channel);
        Mix_FreeChunk(this->chunk);
    }
}

void Sound::Update(float dt) {
}

void Sound::Render() {
}

bool Sound::Is(std::string type) {
    return type == "Sound";
}