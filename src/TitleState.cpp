#include "TitleState.hpp"

#define BACKGROUND_SPRITE "assets/img/title.jpg"
#define CALL_ME_MAYBE "assets/font/Call me maybe.ttf"

#include "Camera.hpp"
#include "Game.hpp"
#include "Text.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "StageState.hpp"
#include "Resources.hpp"
#include <iostream>

TitleState::TitleState(): State() {
    GameObject* background_go = new GameObject();
    Sprite* background_sprite = new Sprite(*background_go,BACKGROUND_SPRITE);
    background_go->box.x = 0;
    background_go->box.y = 0;
    
    GameObject* text_go = new GameObject();
    Text* text = new Text(*text_go,CALL_ME_MAYBE,60,Text::BLENDED,"Aperta espaco ai!",{226,182,8,1},true);
    
    text_go->box.SetSameCenterAs(background_go->box);
    text_go->box.y += background_go->box.h/4;
    text_go->AddComponent(text);
    background_go->AddComponent(background_sprite);

    objectArray.emplace_back(background_go);
    objectArray.emplace_back(text_go);

}
void TitleState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    UpdateArray(dt);
    if(im.KeyPress(SPACE_KEY)) {
        State * toPush = new StageState();
        Game::GetInstance().Push(toPush);
    }
    this->quitRequested = im.QuitRequested() || im.KeyPress(ESCAPE_KEY);
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
}
