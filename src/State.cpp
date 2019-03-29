#define INCLUDE_SDL

#define BACKGROUND_PATH "assets/img/ocean.jpg"
#define STAGE_MUSIC_PATH "assets/audio/stageState.ogg"

#include "SDL_include.h"
#include "State.hpp"
#include <iostream>

State::State() : quitRequested(false), bg(BACKGROUND_PATH), music(STAGE_MUSIC_PATH) {  
    music.Play();
}

void State::LoadAssets() {
}

void State::Render() {
    bg.Render(0,0);
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

bool State::QuitRequested() {
    return quitRequested;
}
