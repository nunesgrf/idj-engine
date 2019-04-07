#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vec2.hpp"
#include "Rect.hpp"
#include "Component.hpp"
#include "GameObject.hpp"
#include <string>

class Collider : public Component {
    private:
        Vec2 scale;
        Vec2 offset;

    public:
        Rect box;

        Collider(GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});  
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
};
#endif