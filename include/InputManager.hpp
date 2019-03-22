#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>

class InputManager {
    private:
        bool mouseState[6];
        int mouseUpdate[6];
        std::unordered_map<int,bool> keyState;
        std::unordered_map<int,int> keyUpdate;
        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;
        InputManager();
        ~InputManager();
    
    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
        static InputManager& GetInstance();
};
#endif 