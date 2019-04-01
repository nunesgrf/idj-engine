#include "../include/Face.hpp"

#define INCLUDE_SDL

#include "SDL_include.h"
#include "Camera.hpp"
#include "Sound.hpp"
#include "InputManager.hpp"
#include <iostream>

Face::Face(GameObject& associated): Component(associated), hitpoints(30) {
}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        associated.RequestDelete();
        Sound * sound = (Sound*)associated.GetComponent("Sound");
        if(sound->Is("Sound")) sound->Play(0);
        
    }
}

void Face::Update(float dt) {
    
    InputManager& inputManager = InputManager::GetInstance();
    
    auto test = inputManager.MousePress(LEFT_MOUSE_BUTTON);
    std::cout << test << std::endl;
    if(test){
        if(associated.box.Contains({(float)inputManager.GetMouseX()+Camera::pos.x,(float)inputManager.GetMouseY()+Camera::pos.y})) {
            Damage(std::rand() % 10 + 10);
        }
    }
}

void Face::Render() {
}

bool Face::Is(std::string type) {
    return type == std::string("Face");
}

void Face::Start() {}