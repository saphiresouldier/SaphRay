//-----------------------------------------------------------------------------
/// camera.h: definition of the CAMERA class
//-----------------------------------------------------------------------------

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "point.h"
#include "color.h"
#include "vector.h"

class CAMERA
{
    public:
            CAMERA();
            CAMERA(POINT o, VECTOR3 d, float f);
            virtual ~CAMERA();

            double fov;
            POINT center;
            VECTOR3 lookat;

            VECTOR3 getPrimaryRayDirection(double i_w, double i_h, int img_width, int img_heigth);
            const POINT getCameraPosition();
};

#endif // CAMERA_H_INCLUDED
