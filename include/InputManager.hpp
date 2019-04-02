#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#define KEY_W SDLK_w
#define KEY_S SDLK_s
#define KEY_A SDLK_a
#define KEY_D SDLK_d
#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_NUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY         SDLK_SPACE

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
    
    public:
        void Update();
        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);
        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);
        int GetMouseX();
        int GetMouseY();
        bool QuitRequested();
        static InputManager& GetInstance();
        ~InputManager();
};
#endif 