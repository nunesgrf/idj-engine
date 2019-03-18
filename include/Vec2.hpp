#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;
        Vec2();
        Vec2(int,int);
        Vec2 GetRotated(float);
        Vec2 operator+(const Vec2);
};
#endif