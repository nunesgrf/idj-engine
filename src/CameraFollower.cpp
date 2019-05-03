#include "CameraFollower.hpp"

#include "Camera.hpp"
CameraFollower::CameraFollower(GameObject& go): Component(go) {

}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
}

bool CameraFollower::Is(std::string type) {
    return type == std::string("CameraFollower");
}

void CameraFollower::Render() {

}
