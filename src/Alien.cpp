#include "Alien.hpp"

#define ALIEN_ROTATION -100
#define SPRITE_ALIEN "assets/img/alien.png"

#include "Collider.hpp"
#include "Sprite.hpp"
#include "Rect.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Minion.hpp"
#include <cstdlib>

Alien::Alien(GameObject& associated, int nMinions):Component(associated), hp(50), speed({100,100})  {
    Sprite* alien_sprite = new Sprite(associated,SPRITE_ALIEN); 
    Collider* col = new Collider(associated);

    associated.AddComponent(col);
    associated.AddComponent(alien_sprite);
    minionArray.resize(nMinions);
}

void Alien::Start() {
    Game &game = Game::GetInstance();
    for(int i = 0; i < minionArray.size(); i++) {
        GameObject* minion_go = new GameObject();

        float setor = (2*i*M_PI)/minionArray.size();
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
        taskQueue.push(action);
    }
    else if(inputManager.MousePress(RIGHT_MOUSE_NUTTON)) {
        Action action(Action::MOVE,x,y);
        taskQueue.push(action);
    }
    if(not taskQueue.empty()) {

        Vec2 alienCenter = associated.box.Center();
        Action action = taskQueue.front();

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
            const std::shared_ptr<GameObject> &ptr = minionArray[ClosestMinion(action.pos)].lock();
            auto minion = (Minion*)ptr->GetComponent("Minion");
            minion->Shoot(action.pos);
            taskQueue.pop();
        }
    }
    associated.angleDeg += ALIEN_ROTATION*dt;
    if(hp <= 0) associated.RequestDelete();
       
}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}

int Alien::ClosestMinion(Vec2 target) {

    int index = 0;
    auto closest = INFINITY;
    for(int i = 0; i < minionArray.size(); i++) {
        float dist = ((minionArray[i].lock())->box.Center() - target).Mag();
        if(closest > dist) {
            closest = dist;
            index = i;
        }
    }
    return index;
}

void Alien::NotifyCollision(GameObject& that) {
    
}

Alien::~Alien() {
    minionArray.clear();
}

void Alien::Render() {}

