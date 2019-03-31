#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.hpp"
#include "Component.hpp"
#include "Vec2.hpp"
#include <string>

class Collider : public Component {
    private:
        Vec2 scale;
        Vec2 offset;
    
    public:
        Collider(GameObject& associated,Vec2 scale = {1,1},Vec2 offset = {0,0});
        Rect box;
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
};
#endif