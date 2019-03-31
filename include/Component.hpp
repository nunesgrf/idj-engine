#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.hpp"
#include <string>

class GameObject;

class Component {
    protected:
        GameObject& associated;

    public:
        Component(GameObject&);
        virtual ~Component();
        void virtual Start();
        void virtual NotifyCollision(GameObject& other);
        void virtual Update(float) = 0;
        void virtual Render() = 0;
        bool virtual Is(std::string) = 0;
};
#endif 