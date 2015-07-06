//-----------------------------------------------------------------------------
/// light.h: definition of the LIGHT class
//-----------------------------------------------------------------------------

#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "point.h"

class LIGHT
{
    public:
            LIGHT() : position(0, 0, 0), intensity(1.0) {}
            LIGHT(POINT pos, float i) : position(pos), intensity(i) {}
            virtual ~LIGHT() {}

            POINT position;
            double intensity;
};

#endif // LIGHT_H_INCLUDED
