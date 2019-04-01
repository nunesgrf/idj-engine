#ifndef RECT_H
#define RECT_H

#include "Vec2.hpp"
#include <vector>

class Rect {
    public:
        float x, y, w, h;
        Rect(float x = 0, float y = 0, float w = 0, float h = 0);
        bool Contains(std::vector<float>);
        Vec2 Center();
        Vec2 CenterOffset();
        Rect operator+(Vec2 that);
        Rect operator/(Vec2 that);
        Rect operator*(Vec2 that);
        Rect operator-(Vec2 that);
        void operator=(Vec2 that);
        void operator+=(Vec2 that);
        void operator*=(Vec2 that);
        void operator-=(Vec2 that);
        void operator/=(Vec2 that);
};
#endif