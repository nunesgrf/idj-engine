#include "Bullet.hpp"

#include "Sprite.hpp"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite): Component(associated) {
    Sprite * sprite = new Sprite(associated,sprite);
}

void Bullet::Update(float dt) {}

bool Bullet::Is(std::string type) {
    return type == std::string("Bullet");
}

int Bullet::GetDamage() {
    return 0;
}

void Bullet::Start() {}
void Bullet::Render() {}

