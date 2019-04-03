#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.hpp"
#include <string>

class GameObject;

class Component {
    protected:
        GameObject& associated;

    public:
        Component(GameObject& associated);
        virtual ~Component();
        void virtual Start();
        void virtual NotifyCollision(GameObject& that);
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool virtual Is(std::string type) = 0;
};
#endif 