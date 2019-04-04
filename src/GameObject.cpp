#include "../include/GameObject.hpp"

#include <algorithm>
#include <iostream>

GameObject::GameObject(): isDead(false), started(false), angleDeg(0) {};

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    std::reverse(components.begin(), components.end());
    for(auto &a : components) {
        a->Update(dt);
    }
    std::reverse(components.begin(), components.end());
}

void GameObject::Render() {
    for(auto &a : components) {
        a->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    components.emplace_back(cpt);
    if(started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = components.begin();
    bool keepGoing = true;

    while(it != components.end() and keepGoing) {
        if(it->get() == cpt) keepGoing = false;
        it++;
    }
    if(it != components.end()) components.erase(it);
}

void GameObject::Start() {
    for(auto &a : components) {
        a->Start();
    }
    started = true;
}

Component* GameObject::GetComponent(std::string type) {
    for(int i = 0; i < components.size(); i++) {
        if(components[i]->Is(type)) return components[i].get();      
    }
    return nullptr;
}

void GameObject::NotifyCollision(GameObject& that) {
    for(int i = 0; i < components.size(); i++) {
        components[i]->NotifyCollision(that);
    }
}

