//-----------------------------------------------------------------------------
/// scene.h: definition of the SCENE class
//-----------------------------------------------------------------------------

#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <vector>
#include <cstdio>
#include <ctype.h>
#include "object.h"
#include "sphere.h"
#include "triangle.h"
#include "light.h"
#include "camera.h"
#include "iostream"

class SCENE
{
    public:
            SCENE() {}
            virtual ~SCENE();

            void placeTriangle(VECTOR3 v1, VECTOR3 v2, VECTOR3 v3, VECTOR3 n, COLOR col);
            void placeSphere(double radius, POINT pos, COLOR col);
            void printSpheres();
            void placeLight(float intensity, POINT pos, COLOR col);
            void printLights();
            void createCamera(POINT center, VECTOR3 direction, float field_of_view);
            void setName(std::string sceneName);
            std::string getName() const;
            bool loadSTL(const char *stl);

            std::vector<GEOMETRY*> geo;
            std::vector<LIGHT> lights;
            CAMERA camera;
            std::string name;
};

#endif // SCENE_H_INCLUDED
