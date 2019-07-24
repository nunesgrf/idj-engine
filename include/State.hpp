#ifndef STATE_H
#define STATE_H

#include "GameObject.hpp"
#include <vector>
#include <memory>

class State {
    protected:
        bool popRequested;
        bool quitRequested;
        bool started;
        std::vector<std::shared_ptr<GameObject>> objectArray;

        void StartArray();
        void virtual UpdateArray(float dt);
        void virtual RenderArray();
    
    public:
        State();
        virtual ~State();

        void virtual LoadAssets() = 0;
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        
        void virtual Start() = 0;
        void virtual Pause() = 0;
        void virtual Resume() = 0;;

        std::weak_ptr<GameObject> virtual AddObject(GameObject* object);
        std::weak_ptr<GameObject> virtual GetObjectPtr(GameObject* object);

        bool PopRequested();
        bool QuitRequested();
};
#endif