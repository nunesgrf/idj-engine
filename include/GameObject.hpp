#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Rect.hpp"
#include "Component.hpp"
#include <vector>
#include <string>
#include <memory>

class Component;

class GameObject{
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;

    public:
        bool started;
        double angleDeg;
        GameObject();
        ~GameObject();
        void Start();
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