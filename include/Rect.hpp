#ifndef RECT_H
#define RECT_H

class Rect {
    public:
        float x, y, w, h;
        Rect();
        bool Contains(float,float);
};
#endif