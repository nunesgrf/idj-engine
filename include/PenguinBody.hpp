#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#define FRICTION 1
#define ACCELETATION 100
#define ANGULAR_SPEED 100
#define MAX_SPEED_REVERSE -5
#define MAX_SPEED_FOWARD 30
#include "Vec2.hpp"
#include "GameObject.hpp"
#include "Component.hpp"
#include <memory>
#include <string>

class PenguinBody : public Component {
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
    
    public:
        static PenguinBody* player;

        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};
#endif