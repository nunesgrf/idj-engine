#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.hpp"
#include "Music.hpp"

class EndState : public State {
    private:
        Music backgroundMusic;
    
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update();
        void Render();

        void Start();
        void Pause();
        void Resume();
};
#endif