#ifndef RECT_H
#define RECT_H

#include <vector>

class Rect {
    public:
        float x, y, w, h;
        Rect();
        bool Contains(std::vector<float> pair);
};
#endif