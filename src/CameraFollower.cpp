#include "CameraFollower.hpp"

#include "Camera.hpp"
CameraFollower::CameraFollower(GameObject& associated): Component(associated) {}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

bool CameraFollower::Is(std::string type) {
    return type == std::string("CameraFollower");
}

void CameraFollower::NotifyCollision(GameObject& that) {
    
}

void CameraFollower::Render() {}
void CameraFollower::Start() {}
