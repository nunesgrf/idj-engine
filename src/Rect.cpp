#include "Rect.hpp"

#include <iostream>
Rect::Rect(float x,float y, float w,float h): x(x), y(y), w(w), h(h) {}

bool Rect::Contains(std::vector<float> point) {
    float x1 = point.front();
    float y1 = point.back();

    if(x > x1 or w+x < x1) return false;
    return y <= y1 and h+y >= y1;
} 

Vec2 Rect::CenterOffset() {
    return Vec2(w/2,h/2);
}

Vec2 Rect::Center() {
    return Vec2(x+w/2,y+h/2);
}

void Rect::operator=(Vec2 that) {
    x = that.x;
    y = that.y;
}

Rect Rect::operator+(Vec2 that) {
    return Rect(x+that.x,y+that.y,w,h);
}

Rect Rect::operator-(Vec2 that) {
    return Rect(x-that.x,y-that.y,w,h);
}

Rect Rect::operator*(Vec2 that) {
    return Rect(x*that.x,y*that.y,w,h);
}

Rect Rect::operator/(Vec2 that) {
    return Rect(x/that.x,y/that.y,w,h);
}

void Rect::operator+=(Vec2 that) {
    *this = *this + that;
}

void Rect::operator-=(Vec2 that) {
    *this = *this - that;
}

void Rect::operator*=(Vec2 that) {
    *this = *this * that;
}

void Rect::operator/=(Vec2 that) {
    *this = *this / that;
}
