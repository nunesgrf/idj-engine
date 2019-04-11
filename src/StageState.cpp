#define INCLUDE_SDL

#define NUM_ALIENS 4

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

	for(int i = 0; i < NUM_ALIENS; i++) {
		GameObject* alien_go = new GameObject();
		alien_go->box.x = rand() % 1408;
		alien_go->box.y = rand() % 1280;
		Alien* alien = new Alien(*alien_go,(rand()%3+3),(rand()%10)/10.0f);
		alien_go->AddComponent(alien);
		objectArray.emplace_back(alien_go);
	}

	GameObject* penguin_go = new GameObject();
	penguin_go->box.x = 704;
	penguin_go->box.y = 640;
	PenguinBody* penguin = new PenguinBody(*penguin_go);
	penguin_go->AddComponent(penguin);

	objectArray.emplace_back(penguin_go);

	Camera::Follow(penguin_go);
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

	if(popRequested) music.Stop(0);

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

            Collider *cA = (Collider*) objectArray[i]->GetComponent("Collider");
            Collider *cB = (Collider*) objectArray[j]->GetComponent("Collider");

            if(cA and cB){
                if (Collision::IsColliding(cA->box, cB->box, (float)(objectArray[i]->angleDeg)*(M_PI/180.0f), (float)(objectArray[j]->angleDeg)*(M_PI/180.0f))) {
                    objectArray[i]->NotifyCollision(*objectArray[j]);
                    objectArray[j]->NotifyCollision(*objectArray[i]);
                }
			}
		}
	}

	
	if(PenguinBody::player == nullptr || Alien::alienCount == 0) {
		
		GameData::playerVictory = (PenguinBody::player != nullptr);
		popRequested = true;
		music.Stop(0);
		Game::GetInstance().Push(new EndState());
	} 
	
}

void StageState::Start() {
	music.Play();
	LoadAssets();
	for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void StageState::Pause() {
	std::cout << "StageState::Pause" << std::endl;
	music.Stop(0);
}

void StageState::Resume() {

}