#include "PenguinBody.hpp"

#define SPRITE_PENGUINBODY "assets/img/penguin.png"

#include "Camera.hpp"
#include "Game.hpp"
#include "InputManager.hpp"
#include "PenguinCannon.hpp"
#include "Sprite.hpp"
#include <iostream>
#include <cmath>

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated): Component(associated), speed({0,0}), linearSpeed(0), angle(0), hp(200) {
    Sprite * pbody_sprite = new Sprite(associated,SPRITE_PENGUINBODY);
    associated.AddComponent(pbody_sprite);
    player = this;
}

PenguinBody::~PenguinBody() {
    player= nullptr;
}

void PenguinBody::Start() {
    GameObject* cannon_go = new GameObject();
    PenguinCannon* cannon = new PenguinCannon(*cannon_go,Game::GetInstance().GetState().GetObjectPtr(&associated));
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
    
    if(linearSpeed > 2) linearSpeed -= FRICTION;
    else if(linearSpeed < 2) linearSpeed += FRICTION;
    
    if(hp <= 0) {
        Camera::Unfollow();
        associated.RequestDelete();
        (*pcannon.lock()).RequestDelete();

    }
    associated.angleDeg = angle;
    speed = Vec2(linearSpeed,0).RotateDeg(angle);
    associated.box += speed;
    (*pcannon.lock()).box.x = associated.box.x;
    (*pcannon.lock()).box.y = associated.box.y;

}

bool PenguinBody::Is(std::string type) {
    return type == std::string("PenguinBody");
}

void PenguinBody::Render() {}

