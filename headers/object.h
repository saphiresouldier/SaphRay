//-----------------------------------------------------------------------------
/// object.h: definition of the SPHERE class
//-----------------------------------------------------------------------------

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "color.h"
#include "point.h"

class SPHERE
{
    public:
            SPHERE() : radius(1.0), center(0, 0, 0), color(0.5, 0.5, 0.5) {}
            SPHERE(double radius, POINT center, COLOR color = COLOR(1.0)) : radius(radius), center(center), color(color) {}
            virtual ~SPHERE() {}

            double radius;
            POINT center;
            COLOR color;
};

#endif // OBJECT_H_INCLUDED
