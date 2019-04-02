#include "PenguinCannon.hpp"

#define SPRITE_PCANNON "assets/img/cubngun.png"
#include "Sprite.hpp"
#include "PenguinBody.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody): Component(associated), angle(0), pbody(penguinBody) {
    Sprite* pcannon_sprite = new Sprite(associated,SPRITE_PCANNON);
    associated.AddComponent(pcannon_sprite);
}

void PenguinCannon::Update(float dt) {
    if(PenguinBody::player != nullptr) {

    }
    else associated.RequestDelete();
}

void PenguinCannon::Shoot() {}

bool PenguinCannon::Is(std::string type) {
    return type == std::string("PenguinCannon");
}

void PenguinCannon::Render() {}