#include "PenguinCannon.hpp"

#define SPRITE_PCANNON "assets/img/cubngun.png"
#define SPRITE_SNOWBALL "assets/img/penguinbullet.png"
#include "Bullet.hpp"
#include "Vec2.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "PenguinBody.hpp"
#include "Collider.hpp"
#include <iostream>

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody): Component(associated), angle(0), pbody(penguinBody) {
    Sprite* pcannon_sprite = new Sprite(associated,SPRITE_PCANNON);
    associated.AddComponent(pcannon_sprite);
}

void PenguinCannon::Update(float dt) {
    InputManager &im = InputManager::GetInstance(); 

    if(PenguinBody::player != nullptr) {
        associated.box.x = PenguinBody::penguin_box.x + (PenguinBody::penguin_box.CenterOffset().x - associated.box.CenterOffset().x);
        associated.box.y = PenguinBody::penguin_box.y + (PenguinBody::penguin_box.CenterOffset().y - associated.box.CenterOffset().y);

        Vec2 mousePos(im.GetMouseX() + Camera::pos.x, im.GetMouseY() + Camera::pos.y);
        Vec2 cannonCenter = associated.box.Center();

        float angle = (mousePos - cannonCenter).InclX();
        this->angle = angle;
        associated.angleDeg = angle*180/M_PI;

        cooldown.Update(dt);
        if(im.MousePress(LEFT_MOUSE_BUTTON)) Shoot();

    }
    else associated.RequestDelete();
}

void PenguinCannon::Shoot() {

    if(cooldown.Get() > 0.4) {
        GameObject* snowball_go = new GameObject();
        Bullet* bullet = new Bullet(*snowball_go,angle,800,10,640,SPRITE_SNOWBALL,4,0.2,false);
        Vec2 offset = Vec2(associated.box.w/2.0 + snowball_go->box.w/2.0).GetRotated(angle);
        snowball_go->AddComponent(bullet);

        snowball_go->box.SetSameCenterAs(associated.box);
        snowball_go->box += offset;
        
        Game::GetInstance().GetState().AddObject(snowball_go);
        cooldown.Restart();
    }
}

bool PenguinCannon::Is(std::string type) {
    return type == std::string("PenguinCannon");
}

void PenguinCannon::Render() {}