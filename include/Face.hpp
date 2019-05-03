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
        void Damage(int);
        void Update(float);
        void Render();
        bool Is(std::string type); 
};
#endif 