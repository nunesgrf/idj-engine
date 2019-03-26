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
        void virtual Update(float) = 0;
        void virtual Render() = 0;
        bool virtual Is(std::string file) = 0;
};
#endif 