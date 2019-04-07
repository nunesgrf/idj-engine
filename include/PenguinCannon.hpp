#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "Timer.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include <memory>
#include <string>

class PenguinCannon : public Component {
    private:
        Timer cooldown;
        std::weak_ptr<GameObject> pbody;
        float angle;
    
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
};
#endif