#include "Game.hpp"
#include "State.hpp"

int main(int argc, char** argv) {

    Game aux = Game::GetInstance();
    aux.Run();
}