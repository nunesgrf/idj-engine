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
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        void NotifyCollision(GameObject& that);
        

        Rect box;        
};
#endif 