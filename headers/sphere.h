#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class SPHERE : public GEOMETRY
{
    public:
            SPHERE() : radius(1.0), center(0, 0, 0), color(0.5, 0.5, 0.5) {}
            SPHERE(double radius, POINT center, COLOR color = COLOR(1.0)) : radius(radius), center(center), color(color) {}
            virtual ~SPHERE() {}

            double radius;
            POINT center;
            COLOR color;

            bool intersect(POINT origin, VECTOR3 direction, double &depth) const;
};

#endif // SPHERE_H
