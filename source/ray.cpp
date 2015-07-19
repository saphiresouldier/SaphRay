//-----------------------------------------------------------------------------
/// ray.cpp: implementation of the ray.h methods
//-----------------------------------------------------------------------------

#include "../headers/ray.h"
#include "../headers/scene.h"

RAY::RAY()  : origin(POINT(0.0f)), direction(VECTOR3(1.0f))
{
}

RAY::RAY(POINT o, VECTOR3 d)  : origin(o), direction(d)
{
}

RAY::~RAY()
{
}

COLOR RAY::shootPrimaryRay(SCENE &scene, double i_w, double i_h,
                            int img_width, int img_heigth)
{
    origin = scene.camera.getCameraPosition();
    direction = scene.camera.getPrimaryRayDirection(i_w, i_h, img_width, img_heigth);

    return collideRay(scene);
}

COLOR RAY::shootRay(const SCENE &scene, POINT o, VECTOR3 d)
{
    origin = o;
    direction = d;
    return collideRay(scene);
}

COLOR RAY::collideRay(const SCENE& scene)
{   
    double current_depth = std::numeric_limits<double>::max(); //proper way?
    COLOR col(0.0), final_col(0.0);
    VECTOR3 sphere_center, normal;
    bool collision = false;
    bool isTriangle = false;
    int sphere_index = -1;

    //collision-----------------------------------
    for(std::vector<SPHERE>::size_type i = 0; i != scene.spheres.size(); i++)
    {
        double collision_depth = 0;
        if(scene.spheres[i].intersect(origin, direction, collision_depth))
        {
            collision = true;
            if(collision_depth < current_depth)
            {
                current_depth = collision_depth;
                col = scene.spheres[i].color;
                sphere_center = VECTOR3(scene.spheres[i].center);
                sphere_index = i;
            }
        }
    }

    for(std::vector<TRIANGLE>::size_type l = 0; l != scene.tris.size(); l++)
    {
        double collision_depth = 0;
        if(scene.tris[l].intersect(origin, direction, collision_depth))
        {
            collision = true;
            if(collision_depth < current_depth)
            {
                current_depth = collision_depth;
                col = scene.tris[l].color;
                //return col;
                normal = scene.tris[l].normal;
                isTriangle = true;
            }
        }
    }

    if(!collision) //background, no shading computation required
        return final_col;

    //compute shading-------------------------------
    VECTOR3 intersection_point(VECTOR3(origin) + (direction*current_depth));
    if(!isTriangle)
    {
        normal = VECTOR3(intersection_point - sphere_center);
        normal.normalize();
    }

    for(std::vector<LIGHT>::size_type j = 0; j != scene.lights.size(); j++)
    {
        bool skip_shading = false;
        VECTOR3 L(VECTOR3(scene.lights[j].position) - intersection_point); //[j]
        //std::cout << "L: " << L.x << " " << L.y << " "<< L.z << " " << std::endl;
        //std::cout << "with intersection point at " << intersection_point.x << " " << intersection_point.y << " " << intersection_point.z << std::endl;
        double dist = L.length();
        //std::cout << "dist: " << dist << std::endl;
        L.normalize();
        RAY shadowray(POINT(intersection_point.x, intersection_point.y, intersection_point.z), L);
        //Lambertian shading----------- 
        double theta = L.dot(normal);
        if(theta >= 0.0f)
        {
            for(std::vector<SPHERE>::size_type k = 0; k != scene.spheres.size(); k++)
            {
                double d = 0.0f, mindepth = 0.001;
                if(scene.spheres[k].intersect(shadowray.origin, shadowray.direction, d))
                {
                    if((mindepth < d) && (d < dist)) //only look for intersections in this range
                    {
                        //std::cout << "collision with sphere: " << k << " with radius: " << scene.spheres[k].radius << " at position " << scene.spheres[k].center.x << " " << scene.spheres[k].center.y << " " << scene.spheres[k].center.z << std::endl;
                        //std::cout << "lightray collide_depth: " << d << std::endl << std::endl;
                        //return final_col;
                        skip_shading = true;
                    }
                }
            }

            if(!skip_shading)
            {
                for(std::vector<TRIANGLE>::size_type m = 0; m != scene.tris.size(); m++)
                {
                    double d = 0.0f, mindepth = 0.001;
                    if(scene.tris[m].intersect(shadowray.origin, shadowray.direction, d))
                    {
                        if((mindepth < d) && (d < dist)) //only look for intersections in this range
                        {
                            //std::cout << "collision with sphere: " << k << " with radius: " << scene.spheres[k].radius << " at position " << scene.spheres[k].center.x << " " << scene.spheres[k].center.y << " " << scene.spheres[k].center.z << std::endl;
                            //std::cout << "lightray collide_depth: " << d << std::endl << std::endl;
                            //return final_col;
                            skip_shading = true;
                        }
                    }
                }
            }

            if(!skip_shading)
            {
                double contribution = (theta * scene.lights[j].intensity) / (dist * dist); //proper inverse square lighting falloff //[j]
                final_col += (col * (scene.lights[j].color * contribution)); //TODO: Clamp this to ensure no artifacts
                //final_col += COLOR(theta); //use this to visualize individual properties
            }
        }
    }

    return final_col;
}
