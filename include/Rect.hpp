#ifndef RECT_H
#define RECT_H

#include "Vec2.hpp"
#include <list>

class Rect {
    public:
        float x, y, w, h;
        Rect(int x = 0, int y = 0, int w = 0, int h = 0);
        bool Contains(std::list<float>);
        Rect sumVec2(Vec2 vec);
        Vec2 Center();
        Rect operator+=(Vec2 v);
};
#endif