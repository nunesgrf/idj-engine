#include "Camera.hpp"

#define INCLUDE_SDL 

#include "SDL_include.h"
#include "Game.hpp"
#include "InputManager.hpp"
#include <iostream>

GameObject* Camera::focus;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(300,300);

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if(focus == nullptr) {
        InputManager& InputManager = InputManager::GetInstance();
        
        bool up = InputManager.IsKeyDown(UP_ARROW_KEY);
        bool down = InputManager.IsKeyDown(DOWN_ARROW_KEY);
        bool left = InputManager.IsKeyDown(LEFT_ARROW_KEY);
        bool right = InputManager.IsKeyDown(RIGHT_ARROW_KEY);

        if(up)    pos.y -= speed.y * dt;
        if(down)  pos.y += speed.y * dt;
        if(left)  pos.x -= speed.x * dt;
        if(right) pos.x += speed.x * dt;
    }
    else {
        pos.x = focus->box.x +focus->box.CenterOffset().x - Game::GetInstance().GetWidth()/2;
        pos.y = focus->box.y +focus->box.CenterOffset().y - Game::GetInstance().GetHeight()/2;
    }
    
}