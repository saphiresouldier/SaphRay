//-----------------------------------------------------------------------------
/// camera.cpp: implementation of the CAMERA class' methods
//-----------------------------------------------------------------------------

#include "../headers/camera.h"

CAMERA::CAMERA()  : center(POINT(0.0f)), lookat(VECTOR3(0.0f)), fov(45.0f)
{
}

CAMERA::CAMERA(POINT o, VECTOR3 d, float f)  : center(o), lookat(d), fov(f)
{
}

CAMERA::~CAMERA()
{
}

VECTOR3 CAMERA::getPrimaryRayDirection(double i_w, double i_h, int img_width, int img_heigth)
{
    VECTOR3 dir(0.0f);

    double aspect_ratio = img_width/(double)img_heigth;
    double angle = tan(fov * 0.5 * M_PI / 180.0);

    double dx = 2.0 * aspect_ratio/(double)img_heigth;
    double dy = 2.0 / (double)img_heigth;

    dir.x = angle * ((i_w + 0.5) * dx - aspect_ratio) + lookat.x;
    dir.y = angle * (-(i_h + 0.5) * dy + 1) + lookat.y;
    dir.z = 1.0;
    dir.normalize();
    return dir;
}

POINT CAMERA::getCameraPosition()
{
    return center;
}
