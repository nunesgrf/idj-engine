#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "GameObject.hpp"
#include "Component.hpp"
#include <memory>
#include <string>

class PenguinCannon : public Component {
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
    
    public:
        PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot();
        void NotifyCollision(GameObject& that);
};
#endif