#include "../include/Vec2.hpp"

#include <cmath>

Vec2::Vec2(int x, int y): x(x), y(y) {
}

Vec2 Vec2::GetRotated(float theta) {
    float x1 = this->x*cos(theta) - this->y*sin(theta);
    float y1 = this->y*cos(theta) + this->x*sin(theta);

    return Vec2(x1,y1);
}

float Vec2::Mag() {
    return std::sqrt((float)std::pow(x,2) + (float)std::pow(y,2));
}
Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(this->x+other.x,this->y+other.y);
}

Vec2 Vec2::operator-(const Vec2 other) {
    return Vec2(this->x-other.x,this->y-other.y);
}

Vec2 Vec2::operator*(const Vec2 other) {
    return Vec2(this->x*other.x,this->y*other.y);
}

void Vec2::operator=(Vec2 other) {
    x = other.x;
    y = other.y;
}

void Vec2::operator*=(Vec2 that) {
    this->x = x*that.x;
    this->y = y*that.y;
}

Vec2 Vec2::AngleX(Vec2 v){
    Vec2 angles(std::cos(ToAngle(v)), std::sin(ToAngle(v)));
    return angles;
}

float Vec2::ToAngle(Vec2 v){
    float teta = std::atan2((v.y - y), (v.x - x));
    return teta;
}

float Vec2::distance(Vec2 that) {
    return std::sqrt(std::pow((this->x-that.x),2) + std::pow((this->y-that.y),2));
}

float Vec2::InclX() {
    return atan2(y, x);
}
