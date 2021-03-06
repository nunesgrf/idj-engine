#ifndef MINION_H
#define MINION_H

#define PI 3.14159265359
#define ANGULAR_SPEED 1

#include "Enemy.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include "Vec2.hpp"
#include <memory>

class Minion : public Component {
    private:
        GameObject& alienCenter;
        float arc;
    
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
        float random_float_in_range(float a, float b);
};
#endif