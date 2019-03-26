#include "Face.hpp"

#define NO_HITPOINTS 0

#include "Sound.hpp"

Face::Face(GameObject& associated): Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= NO_HITPOINTS) {
        associated.RequestDelete();
        Sound * sound = (Sound*)associated.GetComponent("Sound");
        if(sound->Is("Sound")) sound->Play(0);       
    }
}

bool Face::Is(std::string type) {
    return type == std::string("Face");
}

void Face::Render() {}
void Face::Update(float dt) {}