#include "EndState.hpp"

#define VICTORY_AUDIO "assets/audio/endStateLose.ogg"
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
    struct {
        std::string sprite;
        std::string audio;
    } end;

    if(GameData::playerVictory) {
        end.audio = VICTORY_AUDIO;
        end.sprite = VICTORY_SPRITE;
    }
    else {
        end.audio = DEFEAT_AUDIO;
        end.sprite = DEFEAT_SPRITE;
    }

    GameObject* end_go = new GameObject();
    Sprite* end_sprite = new Sprite(*end_go,end.sprite);
    
    end_go->AddComponent(end_sprite);
    objectArray.emplace_back(end_go);
    Music* end_audio = new Music(end.audio);
    end_audio->Play();

    Camera::pos = {0,0};
}

void EndState::Update(float dt) {
    InputManager& im = InputManager::GetInstance();
    if(im.KeyPress(SPACE_KEY)) {
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
}
void EndState::Pause() {}
void EndState::Resume() {
    Camera::pos = {0,0};
}
EndState::~EndState() {}


