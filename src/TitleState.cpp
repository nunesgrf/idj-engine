#include "TitleState.hpp"

#define BACKGROUND_SPRITE "assets/img/title.jpg"

#include "Camera.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"
#include <iostream>

TitleState::TitleState(): State() {
    GameObject* background_go = new GameObject();
    Sprite* background_sprite = new Sprite(*background_go,BACKGROUND_SPRITE);
    background_go->box.x = 0;
    background_go->box.y = 0;
    
    background_go->AddComponent(background_sprite);
    objectArray.emplace_back(background_go);
}

void TitleState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    if(im.KeyPress(SPACE_KEY)) {
        State * toPush = new StageState();
        Game::GetInstance().Push(toPush);
    }
}

void TitleState::Start() {
    LoadAssets();
    for(int i = 0; i < objectArray.size(); i++) {
		objectArray[i]->Start();
	}
	started = true;
}

void TitleState::Render() {
    for(auto &a : objectArray) {
		a->Render();
	}
}
void TitleState::LoadAssets() {}
void TitleState::Pause() {}
void TitleState::Resume() {
    Camera::pos = Vec2(0,0);
}
TitleState::~TitleState() {
    objectArray.clear();
    std::cout << "I'm here" << std::endl;
}
