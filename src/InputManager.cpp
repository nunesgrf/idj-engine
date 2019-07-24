#include "InputManager.hpp"

#define INCLUDE_SDL

#include "SDL_include.h"

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
    
	SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    updateCounter++;

	while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) quitRequested = true;

        if(event.type == SDL_MOUSEBUTTONDOWN or event.type == SDL_MOUSEBUTTONUP) {
            mouseState[(int)event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
            mouseUpdate[(int)event.button.button] = updateCounter;
        }
        else if(event.type == SDL_KEYDOWN or (event.type == SDL_KEYUP) and (bool)not event.key.repeat)  {
            keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] and (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key) {
    return not keyState[key] and (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] and (mouseUpdate[button] == updateCounter);
}

bool InputManager::MouseRelease(int button) {
    return not mouseState[button] and (mouseUpdate[button] == updateCounter);

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

InputManager::~InputManager() {}