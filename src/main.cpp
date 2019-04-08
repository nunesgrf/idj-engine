#include <iostream>
#include "Game.hpp"
#include "StageState.hpp"
int main(int argc, char** argv) {

    Game &exe = Game::GetInstance();
    exe.Push(new StageState());
    exe.Run();

}