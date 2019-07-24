#include "EndState.hpp"

#define VICTORY_AUDIO "assets/audio/endStateWin.ogg"
#define VICTORY_SPRITE "assets/img/win.jpg"
#define DEFEAT_AUDIO "assets/audio/endStateLose.ogg"
#define DEFEAT_SPRITE "assets/img/lose.jpg"
#define CALL_ME_MAYBE "assets/font/Call me maybe.ttf"

#include "StageState.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "GameData.hpp"
#include "Music.hpp"
#include "Text.hpp"
#include "Sprite.hpp"

EndState::EndState() {
    
    std::string sprite = GameData::playerVictory? VICTORY_SPRITE : DEFEAT_SPRITE;
    std::string audio  = GameData::playerVictory? VICTORY_AUDIO  : DEFEAT_AUDIO;
    
    GameObject* end_go = new GameObject();
    Sprite* end_sprite = new Sprite(*end_go,sprite);
    end_go->AddComponent(end_sprite);

    GameObject* quit_text = new GameObject();
    Text* text1 = new Text(*quit_text,CALL_ME_MAYBE,30,Text::BLENDED,"ESC para desistir.",{0,0,0,255},true);
    quit_text->AddComponent(text1);
    quit_text->box.SetSameCenterAs({end_go->box.x,end_go->box.y,end_go->box.w/2,end_go->box.h});

    GameObject* replay_text = new GameObject();
    Text* text2= new Text(*replay_text,CALL_ME_MAYBE,30,Text::BLENDED,"ESPACO para continuar!",{226,182,8,1},true);
    replay_text->AddComponent(text2);
    replay_text->box.SetSameCenterAs({end_go->box.x + end_go->box.w/2,end_go->box.y,end_go->box.w/2,end_go->box.h});

    objectArray.emplace_back(end_go);
    objectArray.emplace_back(quit_text);
    objectArray.emplace_back(replay_text);

    backgroundMusic.Open(audio);    

    Camera::pos = {0,0};
}

void EndState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();

    UpdateArray(dt);
    if(im.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new StageState());
    }
    quitRequested = im.QuitRequested() || im.KeyPress(ESCAPE_KEY);
}

void EndState::LoadAssets() {}
void EndState::Render() {
    RenderArray();
}
void EndState::Start() {
    StartArray();
    backgroundMusic.Play();

}
void EndState::Pause() {
    backgroundMusic.Stop();
}
void EndState::Resume() {
    Camera::pos = {0,0};
    backgroundMusic.Play();
}
EndState::~EndState() {
    objectArray.clear();
}


