#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;
        Vec2(int x = 0,int y = 0);
        Vec2 GetRotated(float);
        Vec2 AngleX(Vec2 other);
        float Mag();
        float ToAngle(Vec2 other);
        float InclX();
        Vec2 operator+(const Vec2 other);
        Vec2 operator-(const Vec2 other);
        Vec2 operator*(const Vec2 other);
        void operator=(Vec2 other);
        void operator*=(Vec2 other);

        float distance(Vec2 that);

};
#endif