#define INCLUDE_SDL

#define ZERO 0
#define BACKGROUND "assets/img/ocean.jpg"
#define STAGE_MUSIC "assets/audio/stageState.ogg"

#include "SDL_include.h"
#include "State.hpp"
#include <iostream>

State::State() : quitRequested(false), bg(BACKGROUND), music(STAGE_MUSIC) {  
    music.Play();
}

void State::LoadAssets() {
}

void State::Render() {
    bg.Render(ZERO,ZERO);
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

bool State::QuitRequested() {
    return quitRequested;
}
