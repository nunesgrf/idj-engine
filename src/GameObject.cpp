#include "../include/GameObject.hpp"

GameObject::GameObject(): isDead(false) {
};

GameObject::~GameObject() {
    for(int i = this->components.size()-1; i >= 0; i--) {
        delete this->components.at(i);
        this->components.pop_back();
    }
}

void GameObject::Update(float dt) {
    for(auto a : this->components) {
        a->Update(dt);
    }
}

void GameObject::Render() {
    for(auto a : this->components) {
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
    // to implement
}

Component* GameObject::GetComponent(std::string type) {
    // to implement
    return nullptr;
}