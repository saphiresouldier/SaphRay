//-----------------------------------------------------------------------------
/// ray.h: definition of the RAY class
//-----------------------------------------------------------------------------

#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include <cmath>
#include <limits>
#include "color.h"
#include "vector.h"
#include "point.h"
#include "scene.h"

class RAY
{
    public:
            RAY();
            RAY(POINT o, VECTOR3 d);
            virtual ~RAY();

            COLOR shootPrimaryRay(SCENE& scene, double i_w, double i_h,
                                    int img_width, int img_heigth);
            COLOR shootRay(const SCENE &scene, POINT o, VECTOR3 d);
            COLOR collideRay(const SCENE &scene);
            bool collideSphere(const SPHERE& sphere, double &depth);

            POINT origin;
            VECTOR3 direction;
};

#endif // RAY_H_INCLUDED