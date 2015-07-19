#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

const double EPSILON = 0.000001;

class TRIANGLE : public GEOMETRY
{
    public:
    TRIANGLE(VECTOR3 v1, VECTOR3 v2, VECTOR3 v3, VECTOR3 norm = VECTOR3(0.0), COLOR col = COLOR(1.0));
            virtual ~TRIANGLE() {}

            VECTOR3 vertex[3];
            VECTOR3 normal;
            COLOR color;

            bool intersect(POINT origin, VECTOR3 direction, double &depth) const;
            void computeNormal();
};

#endif // TRIANGLE_H
