#include "InputManager.hpp"

#define INCLUDE_SDL

#include "SDL_include.h"
#include <iostream>

InputManager& InputManager::GetInstance() {
    static InputManager toReturn;
    return toReturn;
}

InputManager::InputManager(): updateCounter(0), quitRequested(false), mouseX(0), mouseY(0) {
    for(int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}

void InputManager::Update() {
    SDL_Event event;
    
	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    updateCounter++;
	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) quitRequested = true;

        if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                mouseState[(int)event.button.button] = true;
            }
            else {
                mouseState[(int)event.button.button] = false;
            }
            mouseUpdate[(int)event.button.button] = updateCounter;
        }
        else if(event.type == SDL_KEYDOWN || (event.type == SDL_KEYUP) && (bool)!event.key.repeat) {
            if(event.type == SDL_KEYDOWN) {
                keyState[event.key.keysym.sym] = true;
            } 
            else {
                keyState[event.key.keysym.sym] = false;
            }
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && (mouseUpdate[button] == updateCounter);

}

bool InputManager::IsMouseDown(int button) {
    return keyState[button];

}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

InputManager::~InputManager() {

}