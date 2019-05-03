#ifndef STATE_H
#define STATE_H

#include "TileSet.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>

class State {

    private:
        TileSet* tileSet;
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;

        void AddObject(int x,int y);

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
};
#endif