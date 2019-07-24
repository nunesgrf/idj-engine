#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.hpp"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();
};
#endif