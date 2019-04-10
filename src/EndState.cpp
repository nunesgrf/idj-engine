#include "EndState.hpp"

#define VICTORY_AUDIO "assets/audio/endStateWin.ogg"
#define VICTORY_SPRITE "assets/img/win.jpg"
#define DEFEAT_AUDIO "assets/audio/endStateLose.ogg"
#define DEFEAT_SPRITE "assets/img/lose.jpg"

#include "StageState.hpp"
#include "Game.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "GameData.hpp"
#include "Music.hpp"
#include "Sprite.hpp"

EndState::EndState() {
    
    std::string sprite = GameData::playerVictory? VICTORY_SPRITE : DEFEAT_SPRITE;
    std::string audio  = GameData::playerVictory? VICTORY_AUDIO  : DEFEAT_AUDIO;
    
    GameObject* end_go = new GameObject();
    Sprite* end_sprite = new Sprite(*end_go,sprite);
    
    end_go->AddComponent(end_sprite);
    objectArray.emplace_back(end_go);

    backgroundMusic.Open(audio);    

    Camera::pos = {0,0};
}

void EndState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
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


