#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
    protected:
        int hp;

    public:
        Enemy(int hp = 10);
        static bool Being(std::string type);
};
#endif