#include <iostream>
#include "../includes/Game.hpp"
#include "../includes/State.hpp"
int main(int argc, char** argv) {

    Game aux = Game::GetInstance();
    aux.Run();

}