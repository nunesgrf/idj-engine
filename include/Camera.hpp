#ifndef CAMERA_H
#define CAMERA_H

#include "Vec2.hpp"
#include "GameObject.hpp"

class Camera {
    private:
        static GameObject* focus;
    
    public:
        static Vec2 speed;
        static Vec2 pos;
        static void Follow(GameObject * newFocus);
        static void Update(float dt);
        static void Unfollow();
};
#endif 