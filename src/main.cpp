#include <iostream>
#include "../include/Game.hpp"
#include "../include/State.hpp"
int main(int argc, char** argv) {

    Game aux = Game::GetInstance();
    aux.Run();

}