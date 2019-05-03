#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;
        Vec2();
        Vec2(int x,int y);
        Vec2 GetRotated(float a);
        Vec2 operator+(const Vec2);
};
#endif