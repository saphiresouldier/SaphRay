//-----------------------------------------------------------------------------
/// ray.cpp: implementation of the ray.h methods
//-----------------------------------------------------------------------------

#include "../headers/ray.h"
#include "../headers/scene.h"

extern int MAXDEPTH;

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

    return collideRay(scene, 1);
}

COLOR RAY::shootRay(const SCENE &scene, POINT o, VECTOR3 d, int depth)
{
    origin = o;
    direction = d;
    return collideRay(scene, depth + 1);
}

COLOR RAY::collideRay(const SCENE& scene, int depth)
{   
    double current_depth = std::numeric_limits<double>::max();
    COLOR col(0.0), final_col(0.0);
    VECTOR3 normal;
    bool collision = false;
    int geo_index = -1;

    //check for collision with geometry
    for(std::vector<GEOMETRY*>::size_type i = 0; i != scene.geo.size(); i++)
    {
        double collision_depth = 0;
        if(scene.geo[i]->intersect(origin, direction, collision_depth))
        {
            collision = true;
            if(collision_depth < current_depth)
            {
                current_depth = collision_depth;
                col = scene.geo[i]->getColor();
                //sphere_center = VECTOR3(scene.spheres[i].center);
                geo_index = i;
            }
        }
    }

    if(!collision) //background, no shading computation required
        return final_col;
//    else if(collision && (depth >= MAXDEPTH))
//        return col;

    //compute shading-------------------------------
    VECTOR3 intersection_point(VECTOR3(origin) + (direction*current_depth));
    normal = scene.geo[geo_index]->getNormal(intersection_point);

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
            for(std::vector<GEOMETRY*>::size_type k = 0; k != scene.geo.size(); k++)
            {
                double d = 0.0f, mindepth = 0.001;
                if(scene.geo[k]->intersect(shadowray.origin, shadowray.direction, d))
                {
                    if((mindepth < d) && (d < dist)) //only look for intersections in this range
                    {
                        skip_shading = true;
                    }
                }
            }

            if(!skip_shading)
            {
                double contribution = (theta * scene.lights[j].intensity) / (dist * dist); //proper inverse square lighting falloff //[j]
                //TODO: don't calculate refl vector if maxdepth is reached
                //calculate reflection vector
                VECTOR3 view = VECTOR3(origin) - intersection_point;
                view.normalize();
                VECTOR3 refl = normal * (normal.dot(view)) * (2.0) - view;
                refl.normalize();
                COLOR refl_col(0.0);
                RAY *reflection = new RAY(POINT(intersection_point.x + normal.x * 0.001, intersection_point.y + normal.y * 0.001, intersection_point.z + normal.z * 0.001), refl);
                if(depth < MAXDEPTH)
                {
                    refl_col = reflection->collideRay(scene, depth + 1);
                    final_col += ((col * (scene.lights[j].color * contribution)) * 0.7) + (refl_col * 0.3); //TODO: Clamp this to ensure no artifacts
                    //final_col += refl_col;
                }
                else
                {
                    final_col += ((col * (scene.lights[j].color * contribution))); //TODO: Clamp this to ensure no artifacts
                }

                //calculate shading
                //double contribution = (theta * scene.lights[j].intensity) / (dist * dist); //proper inverse square lighting falloff //[j]
                //final_col += ((col * (scene.lights[j].color * contribution)) * 0.5) + (refl_col * 0.5); //TODO: Clamp this to ensure no artifacts
                //final_col += COLOR(theta); //use this to visualize individual properties
                //final_col += refl_col; //use this to visualize individual properties

                if(reflection)
                    delete reflection;
            }
        }
    }

    return final_col;
}
