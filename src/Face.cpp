#include "../include/Face.hpp"

#define INCLUDE_SDL

#include "SDL_include.h"
#include "Sound.hpp"
#include "InputManager.hpp"
#include <iostream>

Face::Face(GameObject& associated): Component(associated), hitpoints(30) {
}

void Face::Damage(int damage) {
    this->hitpoints -= damage;
    if(this->hitpoints <= 0) {
        this->associated.RequestDelete();
        Sound * sound = (Sound*)this->associated.GetComponent("Sound");
        if(sound->Is("Sound")) sound->Play(0);
        
    }
}

void Face::Update(float dt) {
    
    InputManager& inputManager = InputManager::GetInstance();
    
    auto test = inputManager.MousePress(LEFT_MOUSE_BUTTON);
    std::cout << test << std::endl;
    if(test){
        if(this->associated.box.Contains({(float)inputManager.GetMouseX(),(float)inputManager.GetMouseY()})) {
            this->Damage(std::rand() % 10 + 10);
        }
    }
}

void Face::Render() {
}

bool Face::Is(std::string type) {
    return type == std::string("Face");
}