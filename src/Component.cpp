#include "Component.hpp"

Component::Component(GameObject& associated): associated(associated) {}
Component::~Component() {}
void Component::Start() {}

void Collider::NotifyCollision(GameObject& that) {
    
}