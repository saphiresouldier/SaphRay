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
                                    int img_width, int img_heigth, int max_depth);
            COLOR shootRay(const SCENE &scene, POINT o, VECTOR3 d, int cur_depth, int max_depth);
            COLOR collideRay(const SCENE &scene, int cur_depth, int max_depth);
            COLOR computeBackgroundColor(const SCENE& scene);

            POINT origin;
            VECTOR3 direction;

};

#endif // RAY_H_INCLUDED
