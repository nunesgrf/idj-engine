#include "../include/Rect.hpp"
#include <iostream>
Rect::Rect(float x,float y, float w,float h): x(x), y(y), w(w), h(h) {}

bool Rect::Contains(std::list<float> clebinho) {
    // mudar!
    float x1 = clebinho.front();
    float y1 = clebinho.back();

    if(x > x1 or this->w+x < x1) return false;
    return y <= y1 and this->h+y >= y1;
} 

Rect Rect::sumVec2(Vec2 vec) {
    return Rect(x+vec.x,y+vec.y,w,h);
}

Vec2 Rect::Center() {
    return Vec2(x+w/2,y+h/2);
}

Rect Rect::operator+(Vec2 that) {
    return Rect(x+that.x,y+that.y,w,h);
}
void Rect::operator+=(Vec2 that) {
    *this = *this + that;
}

void Rect::operator=(Vec2 that) {
    x = that.x;
    y = that.y;
}

Rect Rect::operator-(Vec2 that) {
    return Rect(x-that.x,y-that.y,w,h);

}
void Rect::operator-=(Vec2 that) {
    *this = *this - that;
}

Vec2 Rect::CenterOffset() {
    return Vec2(w/2,h/2);
}