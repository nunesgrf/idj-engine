#include "../include/Vec2.hpp"

#include <cmath>

Vec2::Vec2(): x(0), y(0) {
}

Vec2::Vec2(int x, int y): x(x), y(y) {
}

Vec2 Vec2::GetRotated(float theta) {
    float x1 = this->x*cos(theta) - this->y*sin(theta);
    float y1 = this->y*cos(theta) + this->x*sin(theta);

    return Vec2(x1,y1);
}

Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(this->x+other.x,this->y+other.y);
}