#define INCLUDE_SDL

#define PI 3.14159265359

#include "SDL_include.h"
#include "CameraFollower.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "TileMap.hpp"
#include "TileSet.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "State.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include <iostream>

State::State() : quitRequested(false), music("assets/audio/stageState.ogg") {
	std::string background_file = "assets/img/ocean.jpg";
	
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go,background_file);
	CameraFollower *cf = new CameraFollower(*go);
    
	go->box.x = 0;
	go->box.y = 0;

	go->AddComponent(sprite);
	go->AddComponent(cf);

	objectArray.emplace_back(go);

	GameObject * tile_go = new GameObject();
	tileSet = new TileSet(*tile_go,64,64,"assets/img/tileset.png");
	TileMap * tilemap = new TileMap(*tile_go,"assets/map/tileMap.txt",tileSet);

	tile_go->AddComponent(tilemap);
	
	objectArray.emplace_back(tile_go);

	music.Play();

}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {
}

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

	if(inputManager.KeyPress(SPACE_KEY)) {
		
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( mouseX, mouseY );
		AddObject((int)objPos.x, (int)objPos.y);
	}
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

void State::AddObject(int mouseX, int mouseY) {
    std::string img = "assets/img/penguinface.png";
	std::string snd = "assets/audio/boom.wav";

    GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go,img);
	Sound* sound = new Sound(*go,snd);
	Face* face = new Face(*go);

	go->box.x = mouseX + Camera::pos.x - sprite->GetWidth()/2.0;
	go->box.y = mouseY + Camera::pos.y - sprite->GetWidth()/2.0;
	go->box.w = sprite->GetWidth();
	go->box.h = sprite->GetHeight();

	go->AddComponent(sprite);
	go->AddComponent(sound);
	go->AddComponent(face);

    objectArray.emplace_back(go);
}

