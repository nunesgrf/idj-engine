#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include "Vec2.hpp"
#include "GameObject.hpp"
#include <string>
#include <memory>

class PenguinBody : public Component {
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        PenguinBody* player;
};
#endif