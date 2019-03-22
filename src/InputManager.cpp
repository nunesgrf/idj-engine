#include "../include/InputManager.hpp"

#define INCLUDE_SDL

#include "../include/SDL_include.h"

InputManager& InputManager::GetInstance() {
    static InputManager toReturn;
    return toReturn;
}

InputManager::InputManager(): updateCounter(0), quitRequested(false), mouseX(0), mouseY(0) {
    for(int i = 0; i < 6; i++) {
        this->mouseState[i] = false;
        this->mouseUpdate[i] = 0;
    }
}

void InputManager::Update() {
    SDL_Event event;
	int mouseX, mouseY;
    
	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

    this->quitRequested = false;

    updateCounter++;
	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) this->quitRequested = true;

        if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                this->mouseState[(int)event.button.button] = true;
            }
            else {
                this->mouseState[(int)event.button.button] = false;
            }
            this->mouseUpdate[(int)event.button.button] = updateCounter;
        }
        else if(event.type == SDL_KEYDOWN || (event.type == SDL_KEYUP) && (bool)event.key.repeat) {
            if(event.type == SDL_KEYDOWN) {
                this->keyState[event.key.keysym.sym] = true;
            } 
            else {
                this->keyState[event.key.keysym.sym] = false;
            }
            this->keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return this->keyState[key] && (this->keyUpdate[key] == this->updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !this->keyState[key] && (this->keyUpdate[key] == this->updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return this->keyState[key];
}

bool InputManager::MousePress(int button) {
    return this->mouseState[button] && (this->mouseUpdate[button] == this->updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !this->mouseState[button] && (this->mouseUpdate[button] == this->updateCounter);

}

bool InputManager::IsMouseDown(int button) {
    return this->keyState[button];

}

int InputManager::GetMouseX() {
    return this->mouseX;
}

int InputManager::GetMouseY() {
    return this->mouseY;
}

bool InputManager::QuitRequested() {
    return this->quitRequested;
}

InputManager::~InputManager() {

}