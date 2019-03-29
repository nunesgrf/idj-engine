#include "Minion.hpp"

#define SPRITE_MINION "assets/img/minion.png"
#include "Sprite.hpp"

Minion::Minion(GameObject& associated,std::weak_ptr<GameObject> alienCenter,float arcOffsetDeg): Component(associated), alienCenter(*alienCenter.lock()) , arc(arcOffsetDeg) {
    Sprite * sprite = new Sprite(associated,SPRITE_MINION);
    this->associated.AddComponent(sprite);

    auto initial = Vec2(200,0).GetRotated(arc);
    this->associated.box += initial;
}

void Minion::Update(float dt) {
 
    arc += ANGULAR_SPEED*0.033;
    Vec2 move = {200,0};
    move = move.GetRotated(arc);
    
    this->associated.box = move + alienCenter.box.Center();
    this->associated.box -= associated.box.CenterOffset();
}

bool Minion::Is(std::string type) {
    return type == std::string("Minion");
}

void Minion::Shoot(Vec2 target) {

} 
void Minion::Render() {}
void Minion::Start() {}