#include "Minion.hpp"

#define SPRITE_MINION "assets/img/minion.png"
#define SPRITE_BULLET_1 "assets/img/minionbullet1.png"
#define MINION_ROTATION -15 

#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"

Minion::Minion(GameObject& associated,std::weak_ptr<GameObject> alienCenter,float arcOffsetDeg): Component(associated), alienCenter(*alienCenter.lock()) , arc(arcOffsetDeg) {
    Sprite * sprite = new Sprite(associated,SPRITE_MINION);
    auto a = random_float_in_range(1,1.5);
    sprite->SetScale(a,a);
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

    associated.angleDeg += MINION_ROTATION;
}

bool Minion::Is(std::string type) {
    return type == std::string("Minion");
}

void Minion::Shoot(Vec2 target) {
 
    /*GameObject* go = new GameObject();
    go->box = associated.box.Center();
    float angle = (target - associated.box.Center()).IncX2()*(180.0f/PI);
    
    Bullet * bullet = new Bullet(*go,angle,300,20,1000,SPRITE_BULLET_1);

    go->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go);*/
    GameObject* go = new GameObject();
    go->box.x = associated.box.Center().x;
    go->box.y = associated.box.Center().y;
    
    Vec2 minionCenter = this->associated.box.Center();

    Bullet * bullet = new Bullet(*go,minionCenter.ToAngle(target),400,10,300,SPRITE_BULLET_1);
    go->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go);

    
} 
float Minion::random_float_in_range(float a, float b) {
    return a + (b - a)*(rand()/(float)RAND_MAX);
}
void Minion::Render() {}
void Minion::Start() {}