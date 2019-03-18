#include "../include/Face.hpp"

Face::Face(GameObject& associated): Component(associated) {
    this->hitpoints = 30;
}

void Face::Damage(int damage) {
    this->hitpoints -= damage;
    if(this->hitpoints <= 0) {
        this->associated.RequestDelete();
        // Dar play no Sound de seu associated se houver um.
    }
}

void Face::Update(float dt) {
}

void Face::Render() {
}

bool Face::Is(std::string type) {
    return type.c_str() == "Face";
}