#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;
        Vec2(int x = 0,int y = 0);
        Vec2 GetRotated(float angle);
        Vec2 operator+(const Vec2);
};
#endif