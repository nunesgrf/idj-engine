#include "Bullet.hpp"

#include "Sprite.hpp"

Bullet::Bullet(GameObject& associated, float angle, float velocidade, int damage, float maxDistance, std::string sprite): Component(associated) {
    Sprite * img = new Sprite(associated,sprite);
    this->associated.AddComponent(img);
    this->speed = Vec2(velocidade,0).GetRotated(angle);
    
    
    this->distanceLeft = maxDistance; 
    
}

void Bullet::Update(float dt) {
    auto move = speed*dt;
    distanceLeft -= speed.Mag()*dt;

    this->associated.box += move;
    if(distanceLeft <= 0) associated.RequestDelete();
}

bool Bullet::Is(std::string type) {
    return type == std::string("Bullet");
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::Start() {}
void Bullet::Render() {}

