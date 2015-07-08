#include "../headers/scene.h"
//-----------------------------------------------------------------------------
/// scene.cpp: implementation of the scene.h methods
//-----------------------------------------------------------------------------

SCENE::~SCENE()
{

}

void SCENE::placeSphere(double radius, POINT pos, COLOR col)
{
    SPHERE sp(radius, pos, col);

    spheres.push_back(sp);
}

void SCENE::printSpheres()
{
    for(std::vector<SPHERE>::size_type i = 0; i != spheres.size(); i++)
    {
        std::cout << "testsphere: " << i << std::endl;
    }
}

void SCENE::placeLight(float intensity, POINT pos, COLOR col)
{
    LIGHT li(pos, intensity, col);

    lights.push_back(li);

}

void SCENE::printLights()
{
    for(std::vector<LIGHT>::size_type i = 0; i != lights.size(); i++)
    {
        std::cout << "testlight: " << i << std::endl;
    }
}

void SCENE::createCamera(POINT center, VECTOR3 direction, float field_of_view)
{
    camera = CAMERA(center, direction, field_of_view);

}
