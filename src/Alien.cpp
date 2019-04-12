#include "Alien.hpp"

#define ALIEN_ROTATION -100
#define SPRITE_ALIEN "assets/img/alien.png"
#define SPRITE_ALIEN_DEATH "assets/img/aliendeath.png"
#define SOUND_ALIEN_DEATH "assets/audio/boom.wav"

#include "PenguinBody.hpp"
#include "Sound.hpp"
#include "Bullet.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Rect.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Minion.hpp"
#include <cstdlib>
#include <iostream>

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions):Component(associated), Enemy(100), speed({200,0})  {
    Sprite* alien_sprite = new Sprite(associated,SPRITE_ALIEN); 

    Collider* col = new Collider(associated,alien_sprite->GetScale());
    associated.AddComponent(col);

    associated.AddComponent(alien_sprite);
    minionArray.resize(nMinions);
    alienCount++;

    state = RESTING;
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
    
    if(state == RESTING) {
        restTimer.Update(dt);
        speed = {200,0};
        if(restTimer.Get() > 0.25) {
            speed *= dt;
            Destination = PenguinBody::penguin_box.Center();
            float angle = (Destination - associated.box.Center()).InclX();
            speed = speed.GetRotated(angle);
            state = MOVING;      
        }
    }
    else {
        Vec2 current = associated.box.Center();
        if(current.distance(Destination) < speed.Mag()) {
            associated.box.x = Destination.x - associated.box.w / 2;
            associated.box.y = Destination.y - associated.box.h / 2;

            Vec2 penguin_pos = PenguinBody::penguin_box.Center();

            if((penguin_pos - current).Mag() > 100) { 
                Vec2 toShoot = ClosestAndFarthestMinions(penguin_pos);
                const std::shared_ptr<GameObject> &ptr1 = minionArray[toShoot.x].lock();
                const std::shared_ptr<GameObject> &ptr2 = minionArray[toShoot.y].lock();

                Minion* minion1 = (Minion*)ptr1->GetComponent("Minion");
                Minion* minion2 = (Minion*)ptr2->GetComponent("Minion");

                minion1->Shoot(penguin_pos);
                minion2->Shoot(penguin_pos);
            }
            else {
                for(int i = 0; i < minionArray.size(); i++) {
                    const std::shared_ptr<GameObject> &ptr = minionArray[i].lock();
                    Minion* minion = (Minion*)ptr->GetComponent("Minion");
                    minion->Shoot(penguin_pos);
                }
            }

            state = RESTING;
            restTimer.Restart();
        }
        else {
            associated.box += speed;
        }
    }
    
    associated.angleDeg += ALIEN_ROTATION*dt;
    if(hp <= 0) {

        associated.RequestDelete();

        GameObject* alien_death = new GameObject();

        alien_death->box = associated.box;

        Sprite* death_sprite = new Sprite(*alien_death,SPRITE_ALIEN_DEATH,4,0.3,1.2);
        Sound* death_sound = new Sound(*alien_death,SOUND_ALIEN_DEATH);

        alien_death->AddComponent(death_sprite);
        alien_death->AddComponent(death_sound);

        Game::GetInstance().GetState().AddObject(alien_death);

        death_sound->Play(0);
        
    }
       
}

bool Alien::Is(std::string type) {
    return type == std::string("Alien");
}

Vec2 Alien::ClosestAndFarthestMinions(Vec2 target) {

    int x = 0;
    int y = 0;
    auto closest = INFINITY;
    auto farthest = -INFINITY;

    for(int i = 0; i < minionArray.size(); i++) {
        float dist = ((minionArray[i].lock())->box.Center() - target).Mag();
        if(closest > dist) {
            closest = dist;
            x = i;
        }
        if(farthest < dist) {
            farthest = dist;
            y = i;
        }
    }
    return {x,y};
}

void Alien::NotifyCollision(GameObject& that) {
    Bullet* bl = (Bullet*)that.GetComponent("Bullet");
    if(bl != nullptr and not bl->targetsPlayer) hp -= bl->GetDamage();
}

Alien::~Alien() {
    alienCount--;
    minionArray.clear();
}

void Alien::Render() {
}

