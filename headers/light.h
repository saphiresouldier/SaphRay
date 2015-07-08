//-----------------------------------------------------------------------------
/// light.h: definition of the LIGHT class
//-----------------------------------------------------------------------------

#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "point.h"
#include "light.h"

class LIGHT
{
    public:
            LIGHT() : position(POINT(0, 0, 0)), intensity(1.0), color(COLOR(1.0)) {}
            LIGHT(POINT pos, float i, COLOR col) : position(pos), intensity(i), color(col) {}
            virtual ~LIGHT() {}

            POINT position;
            double intensity;
            COLOR color;
};

#endif // LIGHT_H_INCLUDED
