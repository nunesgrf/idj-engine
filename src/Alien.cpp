#include "Alien.hpp"

#include "Sprite.hpp"
#include "Rect.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <iostream>

Alien::Alien(GameObject& associated, int nMinions):Component(associated), hp(50), speed({0,0})  {

    Sprite* sprite = new Sprite(associated,"assets/img/alien.png"); //vazamento de memória;
    this->associated.AddComponent(sprite);
    this->associated.box;
}

void Alien::Start() {

}

void Alien::Update(float dt) {
    InputManager &inputManager = InputManager::GetInstance();

    auto x = inputManager.GetMouseX() + Camera::pos.x;
    auto y = inputManager.GetMouseY() + Camera::pos.y;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        Action action(Action::SHOOT,x,y);
        this->taskQueue.push(action);
    }
    else if(inputManager.MousePress(RIGHT_MOUSE_NUTTON)) {
        Action action(Action::MOVE,x,y);
        this->taskQueue.push(action);
    }
    if(not this->taskQueue.empty()) {

        auto alienCenter = this->associated.box.Center();
        auto action = this->taskQueue.front();

        if(action.type == Action::MOVE) {

            Vec2 deltaX(100*dt,0);
            Vec2 calculado = alienCenter - action.pos;
            Vec2 real = deltaX.GetRotated(calculado.InclX());
            
            if(calculado.Mag() < real.Mag()) {
                associated.box += calculado;
                auto a = associated.box;
                taskQueue.pop();
            }
            else {
                associated.box += real;
                auto a = associated.box;
            }
        }
    }

    if(hp <= 0) associated.RequestDelete();
       
}

void Alien::Render() {
}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}
Alien::~Alien() {
    this->minionArray.clear();
}

