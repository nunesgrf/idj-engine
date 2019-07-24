#include "State.hpp"

State::State(): started(false), quitRequested(false), popRequested(false) {}

State::~State() {
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go) {
	std::shared_ptr<GameObject> ptr = std::shared_ptr<GameObject>(go);
	objectArray.push_back(ptr);
	
	if(started) ptr->Start();
	return ptr;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	for(auto &a : objectArray) {
		if(a.get() == go) return std::weak_ptr<GameObject>(a);
	}
	return std::weak_ptr<GameObject>();
}

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for(auto &a : objectArray) {
        a->Start();
    }
}

void State::UpdateArray(float dt) {
    for(auto &a : objectArray) {
        a->Update(dt);
    }
}

void State::RenderArray() {
    for(auto &a : objectArray) {
        a->Render();
    }
}