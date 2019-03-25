#include "Alien.hpp"

#include "Sprite.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <iostream>

Alien::Alien(GameObject& associated, int nMinions): hp(50), speed({100,0}), Component(associated) {

    Sprite* sprite = new Sprite(associated,"assets/img/alien.png"); //vazamento de memória;
    this->associated.AddComponent(sprite);
}

void Alien::Start() {

}

void Alien::Update(float dt) {
    InputManager &inputManager = InputManager::GetInstance();


    if(inputManager.KeyPress(LEFT_MOUSE_BUTTON)) {
        Action action = Action(Action::SHOOT,inputManager.GetMouseX()+Camera::pos.x,inputManager.GetMouseX()+Camera::pos.y); // Vazamento de memória
        this->taskQueue.push(action);
    }
    else if(inputManager.KeyPress(RIGHT_MOUSE_NUTTON)) {
        Action action = Action(Action::MOVE,inputManager.GetMouseX()+Camera::pos.x,inputManager.GetMouseX()+Camera::pos.y); // Vazamento de memória
        this->taskQueue.push(action);
    }
    else {
        if(!this->taskQueue.empty()) {

            auto action = this->taskQueue.front();
            if(action.type == Action::SHOOT) {
                std::cout << "Atirar em x: " << inputManager.GetMouseX()+Camera::pos.x << " y: " << inputManager.GetMouseY()+Camera::pos.y << std::endl;
            }
            else {
                std::cout << "Andar até x: " << inputManager.GetMouseX()+Camera::pos.x << " y: " << inputManager.GetMouseY()+Camera::pos.y << std::endl;

            }
        }
        this->taskQueue.pop();
    }
}

void Alien::Render() {
}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}
Alien::~Alien() {
    this->minionArray.clear();
}
