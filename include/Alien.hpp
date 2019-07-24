#ifndef ALIEN_H
#define ALIEN_H

#define OBJECT_SPEED 100

#include "Sprite.hpp"
#include "Component.hpp"
#include "Enemy.hpp"
#include "Vec2.hpp"
#include <queue>
#include <vector>

class Alien : public Component, public Enemy {
    private:
        enum AlienState {MOVING, RESTING};
        AlienState state;
        Timer restTimer;
        Vec2 Destination;
        float timeOffSet;
        Vec2 speed;
        std::vector<std::weak_ptr<GameObject>> minionArray;
            
    public:
        static int alienCount;
        Alien(GameObject& associated, int nMinions, float timeOffSet);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        Vec2 ClosestAndFarthestMinions(Vec2 target);
        void NotifyCollision(GameObject& that);
};
#endif