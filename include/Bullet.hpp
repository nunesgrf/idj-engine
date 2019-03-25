#ifndef BULLET_H
#define BULLET_H

#include "Component.hpp"
#include "Vec2.hpp"
#include <string>

class Bullet : public Component {
    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
    
    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
        void Update(float dt);
        bool Is(std::string type);
        int GetDamage();
        void Render();
};
#endif