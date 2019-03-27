#ifndef ALIEN_H
#define ALIEN_H

#define OBJECT_SPEED 100

#include "Component.hpp"
#include "Vec2.hpp"
#include <queue>
#include <vector>

class Alien : public Component {
    private:
        class Action {
            public:
                enum ActionType {MOVE, SHOOT};
                Vec2 pos;
                ActionType type;
                Action(ActionType type, float x, float y): type(type), pos({(int)x,(int)y}) {}
        };
        Vec2 speed;
        //int speed;
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
    
    public:
        Alien(GameObject& associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};
#endif