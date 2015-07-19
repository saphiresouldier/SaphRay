//-----------------------------------------------------------------------------
/// vector.cpp: implementation of the vector.h methods
//-----------------------------------------------------------------------------

#include "../headers/vector.h"

VECTOR3::VECTOR3()  : x(0), y(0), z(0)
{
}

VECTOR3::VECTOR3(double xx) : x(xx), y(xx), z(xx)
{
}

VECTOR3::VECTOR3(double xx, double yy, double zz) : x(xx), y(yy), z(zz)
{
}

VECTOR3::VECTOR3(const POINT point)
{
    x = point.x;
    y = point.y;
    z = point.z;
}

VECTOR3::VECTOR3(const COLOR col)
{
    x = col.r;
    y = col.g;
    z = col.b;
}

VECTOR3::~VECTOR3()
{
}

double VECTOR3::length() const
{
    //return sqrtf(x*x + y*y + z*z);
    return sqrt(dot(VECTOR3(x, y, z)));
}

double VECTOR3::dot(VECTOR3 v) const
{
    return x*v.x + y*v.y + z*v.z;
}

VECTOR3 VECTOR3::add(VECTOR3 &v) const
{
    return VECTOR3(x + v.x, y + v.y, z + v.z);
}

VECTOR3 VECTOR3::subtract(VECTOR3 v) const
{
    return VECTOR3(x - v.x, y - v.y, z - v.z);
}

VECTOR3 VECTOR3::cross(VECTOR3 &v) const
{
    return VECTOR3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

void VECTOR3::scale(double factor)
{
    x *= factor;
    y *= factor;
    z *= factor;
}

bool VECTOR3::isNull()
{
    if(x == 0.0 && y == 0.0 && z == 0.0)
        return true;
    return false;
}

void VECTOR3::normalize()
{
    double l = length();
    if(l > 0.0f)
    {
        x /= l;
        y /= l;
        z /= l;
    }
}
