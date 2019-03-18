#ifndef STATE_H
#define STATE_H

#include "Sprite.hpp"
#include "Music.hpp"
#include "GameObject.hpp"
#include <vector>
#include <memory>

class State {

    private:
        Sprite bg;
        Music music;
        bool quitRequested;
        std::vector<std::unique_ptr<GameObject>> objectArray;

        void Input();
        void AddObject(int,int);

    public:
        State();
        ~State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float);
        void Render();
};
#endif