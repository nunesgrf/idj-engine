#include "Minion.hpp"

#define SPRITE_MINION "assets/img/minion.png"
#define SPRITE_BULLET_1 "assets/img/minionbullet1.png"
#define SPRITE_BULLET_2 "assets/img/minionbullet2.png"
#define TEST "assets/img/penguinbullet.png"
#define SPRITE_MINION_DEATH "assets/img/miniondeath.png"
#define SOUND_MINION_DEATH "assets/audio/boom.wav"
#define MINION_ROTATION -400

#include "Sound.hpp"
#include "Alien.hpp"
#include "Collider.hpp"
#include "Sprite.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include <iostream>

Minion::Minion(GameObject& associated,std::weak_ptr<GameObject> alienCenter,float arcOffsetDeg): Component(associated), alienCenter(*alienCenter.lock()) , arc(arcOffsetDeg) {
    Sprite * sprite = new Sprite(associated,SPRITE_MINION);
    
    float scl = random_float_in_range(1.1,1.5);
    sprite->SetScale(scl,scl);

    associated.AddComponent(sprite);

    Vec2 initial = Vec2(200,0).GetRotated(arc);
    associated.box += initial;

}

void Minion::Update(float dt) {
    
    auto aCenterPtr = Game::GetInstance().GetState().GetObjectPtr(&alienCenter);


    if(aCenterPtr.lock() == nullptr) {
        associated.RequestDelete();

        GameObject* minion_death = new GameObject();

        minion_death->box = associated.box;

        Sprite* death_sprite = new Sprite(*minion_death,SPRITE_MINION_DEATH,4,0.3,1.2);
        Sound* death_sound = new Sound(*minion_death,SOUND_MINION_DEATH);

        minion_death->AddComponent(death_sprite);
        minion_death->AddComponent(death_sound);

        Game::GetInstance().GetState().AddObject(minion_death);

        death_sound->Play(0);
        
    }
    else {
        arc += ANGULAR_SPEED*dt;
        Vec2 move = {200,0};
        move = move.GetRotated(arc);
        
        associated.box = move + alienCenter.box.Center();
        associated.box -= associated.box.CenterOffset();

        associated.angleDeg = arc*(180.0f/M_PI);
    }
}
 
bool Minion::Is(std::string type) {
    return type == std::string("Minion");
}

void Minion::Shoot(Vec2 target) {
    GameObject* go = new GameObject();
    go->box.x = associated.box.Center().x;
    go->box.y = associated.box.Center().y;
    
    Vec2 minionCenter = associated.box.Center();

    Bullet * bullet = new Bullet(*go,minionCenter.ToAngle(target),1000,1,500,SPRITE_BULLET_2,3,0.03, true);
    go->AddComponent(bullet);
    Game::GetInstance().GetState().AddObject(go);

    
} 
float Minion::random_float_in_range(float a, float b) {
    return a + (b - a)*(rand()/(float)RAND_MAX);
}

void Minion::Render() {}
void Minion::Start() {}