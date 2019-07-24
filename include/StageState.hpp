#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include "State.hpp"
#include "TileSet.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>

class StageState : public State {

    private:
        TileSet* tileSet;
        Music music;

    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};
#endif