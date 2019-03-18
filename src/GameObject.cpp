#include "../include/GameObject.hpp"

#include <algorithm>

GameObject::GameObject(): isDead(false) {
};

GameObject::~GameObject() {
    this->components.clear();
}

void GameObject::Update(float dt) {
    for(auto &a : this->components) {
        a->Update(dt);
    }
}

void GameObject::Render() {
    for(auto &a : this->components) {
        a->Render();
    }
}

bool GameObject::IsDead() {
    return this->isDead;
}

void GameObject::RequestDelete() {
    this->isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = this->components.begin();
    bool keepGoing = true;

    while(it != this->components.end() and keepGoing) {
        if(it->get() == cpt) keepGoing = false;
        it++;
    }
    if(it != this->components.end()) this->components.erase(it);
}

Component* GameObject::GetComponent(std::string type) {
    for(int i = 0; i < this->components.size(); i++) {
        if(this->components[i]->Is(type)) return this->components[i].get();      
    }
    return nullptr;
}