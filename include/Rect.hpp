#ifndef RECT_H
#define RECT_H

#include <list>

class Rect {
    public:
        float x, y, w, h;
        Rect();
        bool Contains(std::list<float>);
};
#endif