//-----------------------------------------------------------------------------
/// object.h: definition of the SPHERE class
//-----------------------------------------------------------------------------

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

//#include <cmath>
#include <limits>

#include "color.h"
#include "point.h"
#include "vector.h"

class GEOMETRY
{
    public:
            explicit GEOMETRY() {}
            virtual ~GEOMETRY() {}

            virtual bool intersect(POINT origin, VECTOR3 direction, double &depth) const = 0;
            virtual VECTOR3 getNormal(VECTOR3 intersec) const = 0;
            virtual COLOR getColor() const = 0;
};

#endif // OBJECT_H_INCLUDED
