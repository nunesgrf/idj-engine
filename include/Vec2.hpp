#ifndef VEC2_H
#define VEC2_H

class Vec2 {
    private:
        

    public:
        float x, y;
        Vec2(float x = 0,float y = 0);
        Vec2 escalar(float a) const;
        Vec2 GetRotated(float angle);
        Vec2 AngleX(Vec2 that);
        float Mag();
        float ToAngle(Vec2 that);
        float InclX();
        Vec2 RotateDeg(float angle);
        Vec2 operator+(Vec2 that) const;
        Vec2 operator-(Vec2 that) const;
        Vec2 operator*(Vec2 that) const;
        Vec2 operator/(Vec2 that) const;
        void operator+=(Vec2 that);
        void operator-=(Vec2 that);
        void operator*=(Vec2 that);
        void operator/=(Vec2 that);
        Vec2 operator*(float a) const;
        float distance(Vec2 that);

};
#endif