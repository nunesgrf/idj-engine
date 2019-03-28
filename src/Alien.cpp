#include "Alien.hpp"

#include "Sprite.hpp"
#include "Rect.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <iostream>
#include <cstdlib>
#define PI 3.1419

Alien::Alien(GameObject& associated, int nMinions):Component(associated), hp(50), speed({100,100})  {

    Sprite* sprite = new Sprite(associated,"assets/img/alien.png"); //vazamento de memória;
    this->associated.AddComponent(sprite);
    this->associated.box;
}

void Alien::Start() {}

void Alien::Update(float dt) {
    InputManager &inputManager = InputManager::GetInstance();

    auto x = inputManager.GetMouseX() + Camera::pos.x;
    auto y = inputManager.GetMouseY() + Camera::pos.y;

    if(inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        Action action(Action::SHOOT,x,y);
        this->taskQueue.push(action);
    }
    else if(inputManager.MousePress(RIGHT_MOUSE_NUTTON)) {
        std::cout << "x: " << x << " y: " << y << std::endl;
        Action action(Action::MOVE,x,y);
        this->taskQueue.push(action);
    }
    if(not this->taskQueue.empty()) {

        auto alienCenter = this->associated.box.Center();
        auto action = this->taskQueue.front();

        if(action.type == Action::MOVE) {
            
            std::cout << dt <<std::endl;
            Vec2 speedAux = speed*0.03;
            
            Vec2 current = associated.box.Center();
            Vec2 move = action.pos - current;
            auto angle = move.InclX();

            move = Vec2(speed.x * 0.033, 0).GetRotated(angle);

            if(current.distance(action.pos) < speedAux.Mag()) {
                associated.box.x = action.pos.x - associated.box.w / 2;
                associated.box.y = action.pos.y - associated.box.h / 2;
                taskQueue.pop();
            }
            else {
                associated.box += move;
            }
        }
        else {
            taskQueue.pop();
        }
    }
    if(hp <= 0) associated.RequestDelete();
       
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}
Alien::~Alien() {
    this->minionArray.clear();
}

