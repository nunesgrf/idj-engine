#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "GameObject.hpp"
#include "Component.hpp"

#include <string>

class CameraFollower : public Component{
    public:
        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};
#endif 