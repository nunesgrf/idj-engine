#define INCLUDE_SDL

#include "SDL_include.h"
#include <State.hpp>
#include <iostream>

State::State() : quitRequested(false), bg("assets/img/uzumaki.jpg"), music("assets/audio/uzumaki.ogg") {  
    music.Play();
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
