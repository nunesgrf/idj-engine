#include "Bullet.hpp"
#include "Alien.hpp"
#include "PenguinBody.hpp"
#include "Collider.hpp"
#include <iostream>

#define NO_DISTANCE_LEFT 0

Bullet::Bullet(GameObject& associated, float angle, float velocidade, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer): Component(associated), distanceLeft(maxDistance), targetsPlayer(targetsPlayer), damage(damage) {
    Sprite* bullet_sprite = new Sprite(associated,sprite,frameCount,frameTime);
    bullet_sprite->SetScale(1.1,1.1);
    associated.AddComponent(bullet_sprite);
    associated.angleDeg = angle*(180.0/M_PI);
    speed = Vec2(velocidade,0).GetRotated(angle);

    Collider* c = new Collider(associated,{1.1,1.1});
    associated.AddComponent(c);
}

void Bullet::Update(float dt) {
    auto move = speed*dt;
    distanceLeft -= (speed*dt).Mag();

    associated.box += move;
    if(distanceLeft <= NO_DISTANCE_LEFT) associated.RequestDelete();
}

bool Bullet::Is(std::string type) {
    return type == std::string("Bullet");
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject& that) {
    if(targetsPlayer) {
        PenguinBody* pb = (PenguinBody*)that.GetComponent("PenguinBody");
        if(pb != nullptr) associated.RequestDelete();
    }
    else {
        Alien* al = (Alien*)that.GetComponent("Alien");
        if(al != nullptr) {
            associated.RequestDelete();
            std::cout << "Atingiu alien" << std::endl;
        }

    }
}

void Bullet::Start() {}
void Bullet::Render() {}

