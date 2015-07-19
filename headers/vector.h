//-----------------------------------------------------------------------------
/// ray.h: definition of the RAY class
//-----------------------------------------------------------------------------

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#define _USE_MATH_DEFINES
#include <cmath>
#include "point.h"
#include "color.h"

//const double M_PI = 3.1415692;

class VECTOR3
{
    public:
    VECTOR3();
    VECTOR3(double xx);
    VECTOR3(double xx, double yy, double zz);
    VECTOR3(const POINT point);
    VECTOR3(const COLOR col);
    virtual ~VECTOR3();

    double length() const;
    double dot(VECTOR3 &v) const;
    VECTOR3 add(VECTOR3 &v) const;
    VECTOR3 subtract(VECTOR3 &v) const;
    VECTOR3 cross(VECTOR3 &v) const;
    void scale(double factor);
    void normalize();
    VECTOR3 inverted() const {return VECTOR3(-x, -y, -z);}

    VECTOR3 operator * (const double &f) const
    { return VECTOR3(f * x, f * y, f * z); }
    VECTOR3 operator + (const VECTOR3 &c) const
    { return VECTOR3(x + c.x, y + c.y, z + c.z); }
    VECTOR3 operator - (const VECTOR3 &c) const
    { return VECTOR3(x - c.x, y - c.y, z - c.z); }
    VECTOR3 operator * (const VECTOR3 &c) const
    { return double(x * c.x + y * c.y + z * c.z); }
    VECTOR3& operator += (const VECTOR3 &c)
    { x += c.x; y += c.y; z += c.z; return *this; }
    VECTOR3& operator -= (const VECTOR3 &c)
    { x -= c.x; y -= c.y; z -= c.z; return *this; }

    double x, y, z;
};

#endif // VECTOR_H_INCLUDED
