#include "Collider.hpp"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset): Component(associated), scale(scale), offset(offset) {}

void Collider::Update(float dt) {
    Rect copy;
    Rect &aux = associated.box;

    copy.w = aux.w * scale.x;
    copy.h = aux.h * scale.y;

    copy.x = aux.Center().x - copy.w/2;
    copy.y = aux.Center().y - copy.h/2;

    box = aux + offset.RotateDeg(associated.angleDeg);
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

bool Collider::Is(std::string type) {
    return type == std::string("Collider");
}

void Collider::NotifyCollision(GameObject& that) {
    
}

void Collider::Render() {}