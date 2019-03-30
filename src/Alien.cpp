#include "Alien.hpp"

#include "Sprite.hpp"
#include "Rect.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include <iostream>
#include <cstdlib>

#define PI 3.1419
#define ALIEN_ROTATION 1

#include "Game.hpp"
#include "GameObject.hpp"
#include "Minion.hpp"

Alien::Alien(GameObject& associated, int nMinions):Component(associated), hp(50), speed({100,100})  {

    Sprite* sprite = new Sprite(associated,"assets/img/alien.png"); //vazamento de memória;
    this->associated.AddComponent(sprite);
    this->minionArray.resize(nMinions);
}

void Alien::Start() {

    Game &game = Game::GetInstance();
    for(int i = 0; i < minionArray.size(); i++) {
        GameObject* minion_go = new GameObject();

        float setor = (2*i*PI)/minionArray.size();
        Minion * minion = new Minion(*minion_go,game.GetState().GetObjectPtr(&associated),setor);
        minion_go->AddComponent(minion);

        minionArray.at(i) = game.GetState().AddObject(minion_go);
    }
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
            
            Vec2 speedAux = speed*dt;
            
            Vec2 current = associated.box.Center();
            Vec2 move = action.pos - current;
            auto angle = move.InclX();

            move = Vec2(speed.x * dt, 0).GetRotated(angle);

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
            std::cout << "Atirar em " << "x: " << x << " y: " << y << std::endl;

            const std::shared_ptr<GameObject> &ptr = minionArray[ClosestMinion(action.pos)].lock();
            auto minion = (Minion*)ptr->GetComponent("Minion");
            minion->Shoot(action.pos);
            taskQueue.pop();
        }
    }
    this->associated.angleDeg += ALIEN_ROTATION;
    if(hp <= 0) associated.RequestDelete();
       
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}

int Alien::ClosestMinion(Vec2 target) {
    return 0;
}

Alien::~Alien() {
    this->minionArray.clear();
}

