#include "../include/Vec2.hpp"

Vec2::Vec2(): x(0), y(0) {
}

Vec2::Vec2(int x, int y): x(x), y(y) {
}

Vec2 Vec2::GetRotated(float) {
}

Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(this->x+other.x,this->y+other.y);
}