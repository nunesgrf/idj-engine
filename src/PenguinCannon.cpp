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
#include <iostream>

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

        float angle = (mousePos - cannonCenter).InclX();
        this->angle = angle;
        associated.angleDeg = angle*180/M_PI;

        if(im.MousePress(LEFT_MOUSE_BUTTON)) Shoot();
    }
    else associated.RequestDelete();
}

void PenguinCannon::Shoot() {
    GameObject* snowball_go = new GameObject();
    Vec2 offset = Vec2(associated.box.w/2.0,0).GetRotated(angle);
    std::cout << offset.x << " " << offset.y << std::endl;

    Bullet* bullet = new Bullet(*snowball_go,angle,400,10,500,SPRITE_SNOWBALL,4,0.3);
    snowball_go->AddComponent(bullet);

    snowball_go->box.x = associated.box.Center().x  + offset.x;
    snowball_go->box.y = associated.box.Center().y - snowball_go->box.h/2.0 + offset.y;

    Game::GetInstance().GetState().AddObject(snowball_go);

    /*float angle = associated.angleDeg*(M_PI/180);
    GameObject* snowball_go = new GameObject();
    
    snowball_go->box.x = //PenguinBody::go->box.x + associated.box.w;
    snowball_go->box.y = //PenguinBody::go->box.y;

    Bullet* bullet = new Bullet(*snowball_go,angle,400,10,500,SPRITE_SNOWBALL,4,0.3);
    snowball_go->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(snowball_go);*/

}

bool PenguinCannon::Is(std::string type) {
    return type == std::string("PenguinCannon");
}

void PenguinCannon::Render() {}