#include "../headers/scene.h"
//-----------------------------------------------------------------------------
/// scene.cpp: implementation of the scene.h methods
//-----------------------------------------------------------------------------

SCENE::~SCENE()
{
    for(std::vector<GEOMETRY*>::size_type it = 0; it != geo.size(); it++)
    {
        delete geo[it];
    }

    for (std::vector<LIGHT*>::size_type it_l = 0; it_l != lights.size(); it_l++)
    {
      delete lights[it_l];
    }
}

void SCENE::placeTriangle(VECTOR3 v1, VECTOR3 v2, VECTOR3 v3, VECTOR3 n, COLOR col)
{
    try
    {
        geo.push_back(new TRIANGLE(v1, v2, v3, n, col));
    }
    catch(std::bad_alloc &ba)
    {
        std::cerr << "bad_alloc: " << ba.what() << std::endl;
    }

}

void SCENE::placeSphere(double radius, POINT pos, COLOR col)
{
    try
    {
        geo.push_back(new SPHERE(radius, pos, col));
    }
    catch(std::bad_alloc &ba)
    {
        std::cerr << "bad_alloc: " << ba.what() << std::endl;
    }
}

void SCENE::placeLight(float intensity, POINT pos, COLOR col)
{
  try
  {
    lights.push_back(new LIGHT(pos, intensity, col));
  }
  catch (std::bad_alloc& ba)
  {
    std::cerr << "bad_alloc: " << ba.what() << std::endl;
  }
}

void SCENE::setName(std::string sceneName)
{
  name = sceneName;
}

std::string SCENE::getName() const
{
  return name;
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

CAMERA SCENE::getCamera() const
{
  return camera;
}

bool SCENE::loadSTL(const char* stl, COLOR color)
{
    //const char *stl = "suzanne.stl";

    enum { bl, br, tr, tl };
    //Patch *p1 = new Patch(g);
    //p1->setSmoothing(Patch::Faceted);

    FILE* stlfp;
    int i=0,j=0,cnt=0 ,pCnt=4, v_count = 0;
    bool read_normal = true, init = true;
    char a[100];
    char str[40];
    double x=0,y=0,z=0;
    VECTOR3 normal, vertex1, vertex2, vertex3;
    stlfp = fopen(stl,"r");
    if(!stlfp)
    {
        std::cout << "Cannot open .stl file: " << stl << std::endl; //DEBUG
    }
    else
    {
        do  //do for each line in the ascii stl file
        {
            i=0;
            cnt=0;
            std::fgets(a,100,stlfp);
            while(a[i]!='\0')   //advance trough text of line (eg. " Facet Normal ") until end of line
            {
                if(!islower((int)a[i]) && !isupper((int)a[i]) && a[i]!=' ') //stop if current letter is a number
                    break;
                cnt++;
                i++;
            }

            while(a[cnt]!='\0') //read only the numbers and copy them as string into str[]
            {
                str[j]=a[cnt];
                cnt++;
                j++;
            }

            str[j]='\0';    //mark end of string
            j=0;
            if(sscanf(str,"%lf%lf%lf",&x,&y,&z)==3) //copy the values of the numbers from the string into the doubles x,y and z
            {
                if(read_normal)
                {
                    normal.x = x;
                    normal.y = y;
                    normal.z = z;
//                    normal.setX(x);
//                    normal.setY(y);
//                    normal.setZ(z);
                    //normal *= s; //necessary?
                    read_normal = false;
                }
                else if(v_count == 0)
                {
//                    if(init)
//                    {
//                        init_bounds(x, x, z);
//                        init = false;
//                    }
//                    update_bounds(x, y, z);
                    vertex1.x = x;
                    vertex1.y = y;
                    vertex1.z = z;
                    //vertex1 *= s;
                    v_count++;
                }
                else if(v_count == 1)
                {
                    //update_bounds(x, y, z);
                    vertex2.x = x;
                    vertex2.y = y;
                    vertex2.z = z;
                    //vertex2 *= s;
                    v_count++;
                }
                else if(v_count == 2)
                {
                    //update_bounds(x, y, z);
                    vertex3.x = x;
                    vertex3.y = y;
                    vertex3.z = z;
                    //vertex3 *= s;
                    //p1->addTri(vertex1, vertex2, vertex3, normal);
                    geo.push_back(new TRIANGLE(vertex1, vertex2, vertex3, normal, color));

                    read_normal = true;
                    v_count = 0;
                 }
            }
            pCnt++;
        }while(!feof(stlfp));
        fclose(stlfp);
    }
    //p1->setDistances();
    //p1->setTriangleColors(0.f, 2.0f);
    //parts << p1;

//    std::cout << "vcount: " << g->vertices.count() << std::endl;
//    std::cout << " Bounds X: " << min.x() << " to " << max.x() << std::endl;
//    std::cout << " Bounds Y: " << min.y() << " to " << max.y() << std::endl;
//    std::cout << " Bounds Z: " << min.z() << " to " << max.z() << std::endl;

    return true;
}
