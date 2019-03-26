#include "Vec2.hpp"

#include <cmath>

Vec2::Vec2(int x, int y): x(x), y(y) {}

Vec2 Vec2::GetRotated(float theta) {
    float x1 = x*cos(theta) - y*sin(theta);
    float y1 = y*cos(theta) + x*sin(theta);

    return Vec2(x1,y1);
}

Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(x+other.x,y+other.y);
}