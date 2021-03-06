#include <iostream>
#include "Game.hpp"
#include "TitleState.hpp"
#include "StageState.hpp"
#include "Resources.hpp"
int main(int argc, char** argv) {

    Game &exe = Game::GetInstance();
    State* titleState = new TitleState();
    
    exe.Push(titleState);
    exe.Run();

    delete titleState;
    Resources::Clear();
}