#include "EndState.hpp"

#define VICTORY_AUDIO "assets/audio/endStateLose.ogg"
#define VICTORY_SPRITE "assets/img/win.jpg"
#define DEFEAT_AUDIO "assets/audio/endStateLose.ogg"
#define DEFEAT_SPRITE "assets/img/lose.jpg"

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
}

void EndState::Update() {

}

void EndState::LoadAssets() {}
void EndState::Render() {}
void EndState::Start() {}
void EndState::Pause() {}
void EndState::Resume() {}
EndState::~EndState() {}