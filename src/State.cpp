#define INCLUDE_SDL

#include "SDL_include.h"
#include "State.hpp"
#include <iostream>

State::State() : quitRequested(false), bg("assets/img/ocean.jpg"), music("assets/audio/stageState.ogg") {  
    music.Play();
}

State::~State() {
    this->objectArray.clear();
}

void State::LoadAssets() {
}

void State::Render() {
    this->bg.Render(0,0);
}

void State::Update(float dt) {
    this->quitRequested = SDL_QuitRequested();
}

bool State::QuitRequested() {
    return this->quitRequested;
}

void State::Input() {

}

void State::AddObject(int mouseX, int mouseY) {

}
