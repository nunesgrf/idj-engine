#include "../include/Vec2.hpp"

#include <cmath>

Vec2::Vec2(float x, float y): x(x), y(y) {
}

Vec2 Vec2::GetRotated(float theta) {
    float x1 = x*cos(theta) - y*sin(theta);
    float y1 = y*cos(theta) + x*sin(theta);

    return Vec2(x1,y1);
}

float Vec2::Mag() {
    return std::sqrt((float)std::pow(x,2) + (float)std::pow(y,2));
}
Vec2 Vec2::operator+(const Vec2 other) {
    return Vec2(x+other.x,y+other.y);
}

Vec2 Vec2::operator-(const Vec2 other) {
    return Vec2(x-other.x,y-other.y);
}

Vec2 Vec2::operator*(const Vec2 other) {
    return Vec2(x*other.x,y*other.y);
}

Vec2 Vec2::operator/(Vec2 that) {
    return Vec2(x/that.x,y/that.y);
}

void Vec2::operator=(Vec2 other) {
    x = other.x;
    y = other.y;
}

Vec2 Vec2::operator*(float a) {
    return escalar(a);
}

void Vec2::operator+=(Vec2 that) {
    *this = *this+that;
}

void Vec2::operator*=(Vec2 that) {
    x = x*that.x;
    y = y*that.y;
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
    return (*this - that).Mag();
}

float Vec2::InclX() {
    return atan2(y, x);
}

Vec2 Vec2::escalar(float a) {
    return Vec2(x*a,y*a);
}

Vec2 Vec2::RotateDeg(float angle) {
    auto ang = (float)angle*(M_PI/180.0f);
    return Vec2(x*cos(ang)-y*sin(ang),y*cos(ang)+x*sin(ang));
}