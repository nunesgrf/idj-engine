#ifndef MINION_H
#define MINION_H

#include "Component.hpp"
#include "Vec2.hpp"

class Minion : public Component {
    private:
        GameObject& alienCenter;
        float arc;
    
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);
};
#endif