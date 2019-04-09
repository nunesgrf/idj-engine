#include "Face.hpp"

#include "Sound.hpp"

Face::Face(GameObject& associated): Component(associated), hitpoints(30) {}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if(hitpoints <= 0) {
        associated.RequestDelete();
        Sound * sound = (Sound*)associated.GetComponent("Sound");
        if(sound->Is("Sound")) sound->Play(0);
        
    }
}

void Face::Update(float dt) {}
void Face::Render() {}
bool Face::Is(std::string type) {
    return type == std::string("Face");
}