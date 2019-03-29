#ifndef RECT_H
#define RECT_H

#include "Vec2.hpp"
#include <list>

class Rect {
    public:
        float x, y, w, h;
        Rect(float x = 0, float y = 0, float w = 0, float h = 0);
        bool Contains(std::list<float>);
        Rect sumVec2(Vec2 vec);
        Vec2 Center();
        Vec2 CenterOffset();
        Vec2 operator-(Vec2 that);
        Rect operator+=(Vec2 v);
        void operator=(Vec2 that);
        void operator-=(Vec2 that);
};
#endif