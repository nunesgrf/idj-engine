#include "PenguinBody.hpp"

#define SPRITE_PENGUINBODY "assets/img/penguin.png"
#define SPRITE_PENGUIN_DEATH "assets/img/penguindeath.png"
#define SOUND_PENGUIN_DEATH "assets/audio/boom.wav"

#include "Sound.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "InputManager.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include "Collider.hpp"
#include <iostream>
#include <cmath>

PenguinBody* PenguinBody::player;
Rect PenguinBody::penguin_box;

PenguinBody::PenguinBody(GameObject& associated): Component(associated), speed({0,0}), linearSpeed(0), angle(0), hp(200) {
    Sprite * pbody_sprite = new Sprite(associated,SPRITE_PENGUINBODY);
    Collider* col = new Collider(associated);
    associated.AddComponent(col);
    associated.AddComponent(pbody_sprite);
    
    player = this;
    PenguinBody::penguin_box = associated.box;
}

PenguinBody::~PenguinBody() {
    player= nullptr;
}

void PenguinBody::Start() {
    GameObject* cannon_go = new GameObject();
    PenguinCannon* cannon = new PenguinCannon(*cannon_go,Game::GetInstance().GetState().GetObjectPtr(&associated));
    cannon_go->AddComponent(cannon);
    pcannon = Game::GetInstance().GetState().AddObject(cannon_go);
}

void PenguinBody::Update(float dt) {
    InputManager &inputManager = InputManager::GetInstance();

    if(inputManager.IsKeyDown(KEY_W) and MAX_SPEED_FOWARD > linearSpeed) {
        linearSpeed = (linearSpeed + ACCELETATION*dt) < MAX_SPEED_FOWARD ? (linearSpeed + ACCELETATION*dt) : MAX_SPEED_FOWARD; 
    }
    if(inputManager.IsKeyDown(KEY_S) and MAX_SPEED_REVERSE < linearSpeed) {
        linearSpeed = (linearSpeed - ACCELETATION*dt) > MAX_SPEED_REVERSE ? (linearSpeed - ACCELETATION*dt) : MAX_SPEED_REVERSE;
    }
    
    if(inputManager.IsKeyDown(KEY_A)) {
        angle -= ANGULAR_SPEED*dt;
    }
    if(inputManager.IsKeyDown(KEY_D)) {
        angle += ANGULAR_SPEED*dt;
    }
    
    if(linearSpeed > 2) linearSpeed -= FRICTION * dt;
    else if(linearSpeed < 2) linearSpeed += FRICTION * dt;
    
    if(hp <= 0) {
        Camera::Unfollow();
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();

        GameObject* penguin_death = new GameObject();

        penguin_death->box = associated.box;

        Sprite* death_sprite = new Sprite(*penguin_death,SPRITE_PENGUIN_DEATH,5,0.1,0.5);
        Sound* death_sound = new Sound(*penguin_death,SOUND_PENGUIN_DEATH);

        penguin_death->AddComponent(death_sprite);
        penguin_death->AddComponent(death_sound);

        Game::GetInstance().GetState().AddObject(penguin_death);

        death_sound->Play(0);

    }
    associated.angleDeg = angle;
    speed = Vec2(linearSpeed * dt,0).RotateDeg(angle);
    associated.box += speed;

    if(associated.box.x > 1408 - associated.box.w) {
        associated.box.x = 1408 - associated.box.w;
    }
    else if(associated.box.x < 0) {
        associated.box.x = 0;
    }
    if(associated.box.y > 1280 - associated.box.h) {
        associated.box.y = 1280 - associated.box.h;
    }
    else if(associated.box.y < 0) {
        associated.box.y = 0;
    }
    penguin_box = associated.box;


}

bool PenguinBody::Is(std::string type) {
    return type == std::string("PenguinBody");
}

void PenguinBody::NotifyCollision(GameObject& that) {
    Bullet* bl = (Bullet*)that.GetComponent("Bullet");
    if(bl != nullptr and bl->targetsPlayer) hp -= bl->GetDamage();
}

void PenguinBody::Render() {}

