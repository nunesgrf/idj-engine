#include "Enemy.hpp"

Enemy::Enemy(int hp): hp(hp) {}

bool Enemy::Being(std::string type) {
    return type == std::string("Enemy");
}