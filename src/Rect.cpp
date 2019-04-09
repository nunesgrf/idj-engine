#include "../include/Rect.hpp"

Rect::Rect(): x(0), y(0), w(0), h(0) {
}

bool Rect::Contains(std::vector<float> pair) {
    float x1 = pair.front();
    float y1 = pair.back();

    if(x > x1 or w+x < x1) return false;
    return y <= y1 and h+y >= y1;
} 