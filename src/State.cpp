#define INCLUDE_SDL

#include "SDL_include.h"
#include <State.hpp>

State::State() : quitRequested(false) {
}

void State::LoadAssets() {

}

void State::Render() {

}

void State::Update(float dt) {
    this->quitRequested = SDL_QuitRequested();
}

bool State::QuitRequested() {
    return this->quitRequested;
}
