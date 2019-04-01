#include "../include/GameObject.hpp"

#include <algorithm>

GameObject::GameObject(): isDead(false), started(false), angleDeg(0) {};

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for(auto &a : components) {
        a->Update(dt);
    }
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