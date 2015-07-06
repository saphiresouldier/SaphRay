//-----------------------------------------------------------------------------
/// scene.h: definition of the SCENE class
//-----------------------------------------------------------------------------

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include "object.h"
#include "light.h"
#include "camera.h"
#include "iostream"

class SCENE
{
    public:
            SCENE() {}
            virtual ~SCENE();

            void placeSphere(double radius, POINT pos, COLOR col);
            void printSpheres();
            void placeLight(float intensity, POINT pos);
            void printLights();
            void createCamera(POINT center, VECTOR3 direction, float field_of_view);

            std::vector<SPHERE> spheres;
            std::vector<LIGHT> lights;
            CAMERA camera;
};

#endif // SCENE_H_INCLUDED
