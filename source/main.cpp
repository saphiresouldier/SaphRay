//-----------------------------------------------------------------------------
/// main.cpp : Defines the entry point for the application.
//-----------------------------------------------------------------------------

#define DEBUG

#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../headers/scene.h"
#include "../headers/color.h"
#include "../headers/ray.h"
#include "../headers/camera.h"

int IMAGEWIDTH = 512;
int IMAGEHEIGHT = 512;
const char* FILE_EXTENSION = ".bmp";
int MAXDEPTH = 5;

// forward declarations -------------------------------------------------------
bool saveBMP(COLOR** pix, const char* filename);

// main function --------------------------------------------------------------
int main (int argc, char* const argv[])
{

    for(int i = 0; i < argc; i++)
    {
#ifdef DEBUG
        std::cout << "argument " << i << ": " << argv[i] << std::endl;
#endif

        if(!(strcmp(argv[i], "-h")))
        {
            IMAGEHEIGHT = atoi(argv[i+1]);
        }
        else if(!(strcmp(argv[i], "-w")))
        {
            IMAGEWIDTH = atoi(argv[i+1]);
        }
    }
    //Create Scene
    SCENE test_scene;

    // Create Image
    COLOR** pixels;
    try
    {
        pixels = new COLOR*[IMAGEWIDTH];
        for(int i= 0; i < IMAGEWIDTH; ++i)
        {
            pixels[i] = new COLOR[IMAGEHEIGHT];
        }
    }
    catch(std::bad_alloc &ba)
    {
        std::cerr << "bad_alloc: " << ba.what() << std::endl;
    }

// testscene_stl_1----------------------------------------------
    //test_scene.setName("testscene_stl_1");
    //test_scene.placeSphere(2.0, POINT(1.5, -3.0, 2.0), COLOR(0.7f, 0.7f, 0.7f)); //big sphere
    //test_scene.placeSphere(0.6, POINT(-2.0, 2.0, 3.0), COLOR(0.0f, 0.7f, 0.7f)); //small sphere
    //if(test_scene.loadSTL("suzanne_plane_2.stl"))
    //{
    //    std::cout << "STL file loaded" << std::endl;
    //}
    //test_scene.placeLight(50.0, POINT(-3.0, 2.5, -5.0), COLOR(1.0));
    //test_scene.createCamera(POINT(0.5f, 0.0, -5.0), VECTOR3(0.0f, 0.0f, 1.0f), 60.0f);

// testscene_triangle_1----------------------------------------
    test_scene.setName("testscene_triangle_1");
    test_scene.placeSphere(2.0, POINT(0.0, -2.5, 7.0), COLOR(0.7f, 0.7f, 0.7f)); //big sphere
    test_scene.placeSphere(0.6, POINT(-2.0, 2.0, 6.0), COLOR(0.0f, 0.7f, 0.7f)); //small sphere
    test_scene.placeTriangle(VECTOR3(0.0, 1.0, 5.0), VECTOR3(0.0, -1.0, 5.0), VECTOR3(-1.5, 0.0, 5.0), VECTOR3(0.0, 0.0, -1.0), COLOR(0.8));
    test_scene.placeLight(40.0, POINT(-3.0, 2.5, 0.0), COLOR(1.0));
    test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 60.0f);

// testscene_1-------------------------------------------------
    /*test_scene.setName("testscene_1");
    test_scene.placeSphere(2.0, POINT(0.0, -3.0, 6.0), COLOR(0.7f, 0.7f, 0.7f));
    test_scene.placeSphere(0.6, POINT(-2.0, 3.0, 9.0), COLOR(0.0f, 0.7f, 0.7f));
    test_scene.placeSphere(0.5, POINT(0.0, 0.0, 5.0), COLOR(0.8f, 0.0f, 0.5f));
    test_scene.placeLight(70.0, POINT(-2.0, 10.0, 3.0), COLOR(1.0));
    test_scene.placeLight(50.0, POINT(2.0, 10.0, 0.0), COLOR(1.0));
    test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 45.0f);*/

//testscene_2---------------------------------------------------
    //test_scene.setName("testscene_2");
    //test_scene.placeSphere(1.0, POINT(0.0, 1.0, 6.0), COLOR(0.0f, 0.0f, 0.8f)); //blue
    //test_scene.placeSphere(2.0, POINT(0.0, -1.0, 10.0), COLOR(0.0f, 1.0f, 0.0f)); //green
    //test_scene.placeSphere(51.0, POINT(53.0, 0.0, 8.0), COLOR(0.8f, 0.8f, 0.8f)); //"ground plane"
    //test_scene.placeLight(200.0, POINT(-20.0, 0.0, 8.0), COLOR(1.0)); //set intesity higher in case of black render
    //test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 45.0f);

//testscene_depth-----------------------------------------------
    /*test_scene.setName("testscene_depth");
    test_scene.placeSphere(2.0, POINT(0.0, 0.0, 10.0), COLOR(0.5f, 1.0f, 0.0f));
    test_scene.placeSphere(0.5, POINT(0.0, 0.0, 6.0), COLOR(0.0f, 0.0f, 0.8f));
    test_scene.placeLight(150.0, POINT(-2.0, 2.0, 0.0), COLOR(1.0));
    test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 45.0f);*/

    const clock_t begin_time = clock();

    for(int j = 0; j < IMAGEHEIGHT; j++)
    {
        for(int i = 0; i < IMAGEWIDTH; i++)
        {
            //Scale view plane for aspect ratio fix (otherwise image looks stretched)
            double uScale = 1.0;
            double vScale = 1.0;
            if(IMAGEWIDTH > IMAGEHEIGHT)
                uScale = (double) IMAGEWIDTH / IMAGEHEIGHT;
            else if(IMAGEWIDTH < IMAGEHEIGHT)
                vScale = (double) IMAGEHEIGHT / IMAGEWIDTH;

            RAY primray;
            pixels[i][j] = primray.shootPrimaryRay(test_scene, (double)j * vScale, (double)i * uScale, IMAGEWIDTH, IMAGEHEIGHT);

        }
    }

    float seconds = float(clock() - begin_time) / CLOCKS_PER_SEC;
    int min = seconds / 60;
    std::cout << "Rendertime: " << min << " min, " << seconds - (min * 60.0) << " seconds" << std::endl;

    // Save rendered image to disk
    std::string filename = test_scene.getName().append(FILE_EXTENSION);
    if(saveBMP(pixels, filename.c_str()))
    {
        std::cout << "File written to: " << filename << std::endl;
    }
    else
    {
        std::cout << "Error writing file!" << std::endl;
    }

    // Free allocated memory
    for(int i = 0; i < IMAGEWIDTH; ++i)
    {
        delete [] pixels[i];
    }
    delete [] pixels;


	return 0;
}


bool saveBMP(COLOR** pix, const char* filename)
{
    FILE *file_bmp;
    int file_size = 54 + 3*IMAGEWIDTH*IMAGEHEIGHT;

    unsigned char* image = NULL;
    image = (unsigned char *)malloc(3*IMAGEWIDTH*IMAGEHEIGHT);
    memset(image, 0, sizeof(image));

    //BMP headers
    unsigned char bmp_file_header[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmp_info_header[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmp_pad[3] = {0,0,0};

    bmp_file_header[2]  = (unsigned char)(file_size);
    bmp_file_header[3]  = (unsigned char)(file_size >> 8);
    bmp_file_header[4]  = (unsigned char)(file_size >> 16);
    bmp_file_header[5]  = (unsigned char)(file_size >> 24);

    bmp_info_header[4]  = (unsigned char)(IMAGEWIDTH);
    bmp_info_header[5]  = (unsigned char)(IMAGEWIDTH >> 8);
    bmp_info_header[6]  = (unsigned char)(IMAGEWIDTH >> 16);
    bmp_info_header[7]  = (unsigned char)(IMAGEWIDTH >> 24);
    bmp_info_header[8]  = (unsigned char)(IMAGEHEIGHT);
    bmp_info_header[9]  = (unsigned char)(IMAGEHEIGHT >> 8);
    bmp_info_header[10] = (unsigned char)(IMAGEHEIGHT >> 16);
    bmp_info_header[11] = (unsigned char)(IMAGEHEIGHT >> 24);

    file_bmp = fopen(filename, "wb");
    if(!file_bmp)
    {
        return false;
    }

    fwrite(bmp_file_header, 1, 14, file_bmp);
    fwrite(bmp_info_header, 1, 40, file_bmp);

    for(int j = 0; j < IMAGEHEIGHT; j++)
    {
        for(int i = 0; i < IMAGEWIDTH; i++)
        {
            image[(i+j*IMAGEWIDTH)*3 + 2] = (unsigned char)(255.0*pix[i][j].r + 0.5);
            image[(i+j*IMAGEWIDTH)*3 + 1] = (unsigned char)(255.0*pix[i][j].g + 0.5);
            image[(i+j*IMAGEWIDTH)*3 + 0] = (unsigned char)(255.0*pix[i][j].b + 0.5);
        }
    }

    for(int l = 0; l < IMAGEHEIGHT; l++)
    {
        fwrite(image+(IMAGEWIDTH*(IMAGEHEIGHT-l-1)*3), 3, IMAGEWIDTH, file_bmp);
        fwrite(bmp_pad, 1, (4-(IMAGEWIDTH*3)%4)%4, file_bmp);
    }

    fclose(file_bmp);
    free(image);

    return true;
}
