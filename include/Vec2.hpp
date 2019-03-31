#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    public:
        float x, y;
        Vec2(float x = 0,float y = 0);
        Vec2 GetRotated(float);
        Vec2 AngleX(Vec2 other);
        float Mag();
        float ToAngle(Vec2 other);
        float InclX();
        float IncX2();
        Vec2 RotateDeg(float angle);
        Vec2 escalar(float a);
        Vec2 operator+(const Vec2 other);
        Vec2 operator-(const Vec2 other);
        Vec2 operator*(const Vec2 other);
        void operator=(Vec2 other);
        void operator +=(Vec2 that);
        void operator*=(Vec2 other);
        Vec2 operator*(float a);
        float distance(Vec2 that);

};
#endif