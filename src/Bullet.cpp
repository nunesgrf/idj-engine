#include "Bullet.hpp"

#define NO_DISTANCE_LEFT 0

Bullet::Bullet(GameObject& associated, float angle, float velocidade, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime): Component(associated) {
    Sprite* bullet_sprite = new Sprite(associated,sprite,frameCount,frameTime);
    associated.AddComponent(bullet_sprite);
    associated.angleDeg = angle*(180.0/M_PI);
    speed = Vec2(velocidade,0).GetRotated(angle);
    
    distanceLeft = maxDistance;  
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

void Bullet::Start() {}
void Bullet::Render() {}

