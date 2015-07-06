//-----------------------------------------------------------------------------
/// ray.h: definition of the POINT class
//-----------------------------------------------------------------------------

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

struct POINT
{
    POINT() : x(0), y(0), z(0) {}
    POINT(double xx) : x(xx), y(xx), z(xx) {}
    POINT(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
    POINT(const POINT& p) {x = p.x; y = p.y; z = p.z;}

    double x, y, z;
};

#endif // POINT_H_INCLUDED
