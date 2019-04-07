#ifndef FACE_H  
#define FACE_H

#include "GameObject.hpp"
#include "Component.hpp"
#include <string>

class Face : public Component {
    private:
        int hitpoints;

    public:
        Face(GameObject& associated);
        void Start();
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type); 
};
#endif 