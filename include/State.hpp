#ifndef STATE_H
#define STATE_H

#include "Sprite.hpp"
#include "Music.hpp"

class State {

    private:
        Sprite bg;
        Music music;
        bool quitRequested;

    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float);
        void Render();
};
#endif