#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.hpp"
#include "Component.hpp"
#include <vector>
#include <string>

class Component;

class GameObject{
    private:
        std::vector<Component*> components;
        bool isDead;

    public:
        GameObject();
        ~GameObject();

        void Update(float);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component*);
        void RemoveComponent(Component*);
        Component* GetComponent(std::string);

        Rect box;        
};
#endif 