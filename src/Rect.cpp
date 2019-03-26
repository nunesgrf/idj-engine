#include "Rect.hpp"

Rect::Rect(): x(0), y(0), w(0), h(0) {}

bool Rect::Contains(std::list<float> point) {
    float x1 = point.front();
    float y1 = point.back();

    if(x > x1 or this->w+x < x1) return false;
    return y <= y1 and this->h+y >= y1;
} 