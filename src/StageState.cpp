#define INCLUDE_SDL

#include "SDL_include.h"
#include "Collider.hpp"
#include "Collision.h"
#include "CameraFollower.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "TileMap.hpp"
#include "Alien.hpp"
#include "TileSet.hpp"
#include "Face.hpp"
#include "Vec2.hpp"
#include "StageState.hpp"
#include "Sprite.hpp"
#include "Sound.hpp"
#include "PenguinBody.hpp"
#include "GameData.hpp"
#include "EndState.hpp"
#include "Alien.hpp"
#include "Game.hpp"
#include <iostream>


StageState::StageState() : State(), music("assets/audio/stageState.ogg") {
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
	Alien* alien = new Alien(*alien_go,4);
	alien_go->AddComponent(alien);

	objectArray.emplace_back(alien_go);

	GameObject* penguin_go = new GameObject();
	penguin_go->box.x = 704;
	penguin_go->box.y = 640;
	PenguinBody* penguin = new PenguinBody(*penguin_go);
	penguin_go->AddComponent(penguin);

	objectArray.emplace_back(penguin_go);

	Camera::Follow(penguin_go);
	music.Play();

}

StageState::~StageState() {
    objectArray.clear();
}

void StageState::LoadAssets() {
}

void StageState::Render() {
	for(auto &a : objectArray) {
		a->Render();
	}
}

void StageState::Update(float dt) {
	
	InputManager& inputManager = InputManager::GetInstance();

	Camera::Update(dt);
	quitRequested = inputManager.QuitRequested();
	popRequested = inputManager.KeyPress(ESCAPE_KEY);

	int mouseX = inputManager.GetMouseX();
	int mouseY = inputManager.GetMouseY();
	
	int limit = objectArray.size();

	for(int i = 0; i < limit; i++) {
		objectArray[i]->Update(dt);
	}

	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin()+i);
		}
	}

	for(int i = 0; i < objectArray.size(); i++) {
		for(int j = i+1; j < objectArray.size(); j++) {
			auto &objA = objectArray[i];
            auto &objB = objectArray[j];

            Collider *colliderA = (Collider*) objA->GetComponent("Collider");
            Collider *colliderB = (Collider*) objB->GetComponent("Collider");
            if(i != j and colliderA != nullptr && colliderB != nullptr){
                auto boxA = colliderA->box;
                auto boxB = colliderB->box;

                auto angleOfA = (float)(objA->angleDeg)*(M_PI/180.0f);
                auto angleOfB = (float)(objB->angleDeg)*(M_PI/180.0f);

                if (Collision::IsColliding(boxA, boxB, angleOfA, angleOfB)) {
                    objA->NotifyCollision(*objB);
                    objB->NotifyCollision(*objA);
                }
			}
		}
	}

	
	if(PenguinBody::player == nullptr || Alien::alienCount == 0) {
		
		GameData::playerVictory = (PenguinBody::player != nullptr);
		Game::GetInstance().Push(new EndState());
	} 
	
}

void StageState::Start() {
	LoadAssets();
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void StageState::Pause() {
	music.Stop();
}

void StageState::Resume() {

}