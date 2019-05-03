#include "../include/Rect.hpp"

Rect::Rect(): x(0), y(0), w(0), h(0) {
}

bool Rect::Contains(std::vector<float> vec) {
    float x1 = vec[0];
    float y1 = vec[1];

    if(x > x1 or this->w+x < x1) return false;
    return y <= y1 and this->h+y >= y1;
} 