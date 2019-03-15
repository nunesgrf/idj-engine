#include <iostream>
#include "../includes/Game.hpp"

int main(int argc, char** argv) {

    std::cout << "Olá, mundo!" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    Game * aux;
    aux->GetInstance();
}