#define INCLUDE_SDL

#include "SDL_include.h"
#include "CameraFollower.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "TileMap.hpp"
#include "Alien.hpp"
#include "TileSet.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "State.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include <iostream>


State::State() : quitRequested(false), music("assets/audio/stageState.ogg"), started(false) {
	std::string background_file = "assets/img/ocean.jpg";
	
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go,background_file);
	CameraFollower *cf = new CameraFollower(*go);
	go->box.x = 0;
	go->box.y = 0;

	go->AddComponent(sprite);
	go->AddComponent(cf);

	objectArray.emplace_back(go);

	GameObject* tile_go = new GameObject();
	tileSet = new TileSet(*tile_go,64,64,"assets/img/tileset.png");
	TileMap * tilemap = new TileMap(*tile_go,"assets/map/tileMap.txt",tileSet);

	tile_go->AddComponent(tilemap);
	objectArray.emplace_back(tile_go);

	GameObject* alien_go = new GameObject();
	alien_go->box.x = 512;
	alien_go->box.y = 300;
	Alien* alien = new Alien(*alien_go,6);
	alien_go->AddComponent(alien);

	objectArray.emplace_back(alien_go);

	music.Play();

}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {}

void State::Render() {
	for(auto &a : objectArray) {
		a->Render();
	}
}

void State::Update(float dt) {
	
	InputManager& inputManager = InputManager::GetInstance();

	Camera::Update(dt);
	quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
	int mouseX = inputManager.GetMouseX();
	int mouseY = inputManager.GetMouseY();
	
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Update(dt);
	}
	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin()+i);
		}
	}
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start() {
	LoadAssets();
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
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
