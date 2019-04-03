#include "PenguinCannon.hpp"

#define SPRITE_PCANNON "assets/img/cubngun.png"

#include "Vec2.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "PenguinBody.hpp"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody): Component(associated), angle(0), pbody(penguinBody) {
    Sprite* pcannon_sprite = new Sprite(associated,SPRITE_PCANNON);
    associated.AddComponent(pcannon_sprite);
}

void PenguinCannon::Update(float dt) {
    InputManager &im = InputManager::GetInstance(); 

    if(PenguinBody::player != nullptr) {
        associated.box.x = PenguinBody::go->box.x + (PenguinBody::go->box.CenterOffset().x - associated.box.CenterOffset().x);
        associated.box.y = PenguinBody::go->box.y + (PenguinBody::go->box.CenterOffset().y - associated.box.CenterOffset().y);

        Vec2 mousePos(im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y);
        Vec2 cannonCenter = associated.box.Center();

        auto angle = (mousePos - cannonCenter).InclX();
        associated.angleDeg = angle*180/M_PI;
    }
    else associated.RequestDelete();
}

void PenguinCannon::Shoot() {}

bool PenguinCannon::Is(std::string type) {
    return type == std::string("PenguinCannon");
}

void PenguinCannon::Render() {}