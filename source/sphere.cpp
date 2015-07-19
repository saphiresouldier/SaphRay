//-----------------------------------------------------------------------------
/// sphere.cpp: implementation of the sphere.h methods
//-----------------------------------------------------------------------------

#include "../headers/sphere.h"

bool SPHERE::intersect(POINT origin, VECTOR3 direction, double& depth) const
{
    depth = std::numeric_limits<double>::max();
    //geometric method
    VECTOR3 sphere_ray = VECTOR3(center).subtract(VECTOR3(origin));
    //sqare distance to center of sphere
    double sq_dist = sphere_ray.dot(sphere_ray);
    // distance to point on ray closest to sphere center
    double dist_cl_point = sphere_ray.dot(direction);

    bool outside = sq_dist > (radius * radius);
    if(dist_cl_point < 0 && outside)
    {
        return false;
    }

    //square distance from sphere.center to closest point on ray
    double sq_dist_sphere_cl_point = sq_dist - dist_cl_point*dist_cl_point;
    //square distance from perpendicluar bisector to center
    double sq_dist_bisec_center = (radius * radius) - sq_dist_sphere_cl_point;

    if(sq_dist_bisec_center < 0)
        return false;
    double z_depth;
    if(outside)
        z_depth = dist_cl_point - sqrt(sq_dist_bisec_center);
    else
        z_depth = dist_cl_point + sqrt(sq_dist_bisec_center);

    if(z_depth < 0)
        return false;

    depth = z_depth;
    //DEBUG std::cout << "z_depth: " << z_depth << std::endl;
    return true;
}
