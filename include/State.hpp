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
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        std::weak_ptr<GameObject> AddObject(GameObject* go);
        std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
};
#endif