#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#define ACCELETATION 50
#define ANGULAR_SPEED 100
#define MAX_SPEED 20

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