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
#include <thread>
#include <vector>

#include "../headers/scene.h"
#include "../headers/color.h"
#include "../headers/ray.h"
#include "../headers/camera.h"
#include "../headers/rng.h"

// config parameters ---------------------------------------------------------
int IMAGEWIDTH = 600;
int IMAGEHEIGHT = 400;
const int SAMPLES_PER_PIXEL = 8;
const int MAXDEPTH = 3;
const char* FILE_EXTENSION = ".bmp"; 

static thread_local uint32_t seed_state = 1337;

// forward declarations -------------------------------------------------------
bool saveBMP(COLOR** pix, const char* filename);

void shootPrimaryRaySamples(COLOR**& pixels, const int j, const SCENE& test_scene, unsigned long& raycounter)
{
  for (int i = 0; i < IMAGEWIDTH; i++)
  {
    for (int k = 0; k < SAMPLES_PER_PIXEL; k++)
    {
      //Scale view plane for aspect ratio fix (otherwise image looks stretched)
      double uScale = 1.0;
      double vScale = 1.0;
      if (IMAGEWIDTH > IMAGEHEIGHT)
        uScale = (double)IMAGEWIDTH / IMAGEHEIGHT;
      else if (IMAGEWIDTH < IMAGEHEIGHT)
        vScale = (double)IMAGEHEIGHT / IMAGEWIDTH;

      uScale = 1.0 / uScale;
      vScale = 1.0 / vScale;

      RAY primray;
      pixels[i][j] += primray.shootPrimaryRay(test_scene, ((double)i + RandomFloat01(seed_state)) * uScale, ((double)j + RandomFloat01(seed_state)) * vScale, IMAGEWIDTH, IMAGEHEIGHT, MAXDEPTH, raycounter);
    }

    pixels[i][j] /= SAMPLES_PER_PIXEL;
  }
}

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

    const clock_t begin_building_scene = clock();

    // Create Scene
    SCENE test_scene;

// testscene_stl_1----------------------------------------------
    //test_scene.setName("testscene_stl_1");
    //test_scene.placeSphere(2.0, POINT(4.0, 2.0, 2.0), COLOR(1.0f, 1.0f, 1.0f)); //big sphere
    //test_scene.placeSphere(0.6, POINT(-3.0, 2.0, 3.0), COLOR(0.0f, 0.7f, 0.7f)); //small sphere
    //test_scene.placeSphere(0.7, POINT(-5.5, 4.0, 3.0), COLOR(1.0f, 0.6f, 0.0f)); //small sphere
    //test_scene.loadSTL("../models/suzanne_4.stl", COLOR(0.5f, 0.5f, 0.5f));  // stl mesh
    //test_scene.loadSTL("../models/plane_1.stl", COLOR(0.5f, 0.5f, 0.5f));  // stl mesh
    //test_scene.placeLight(500.0, POINT(-13.0, 2.5, -15.0), COLOR(1.0));
    //test_scene.createCamera(POINT(0.0f, 4.0f, -10.0), VECTOR3(0.0f, -0.3f, 1.0f), 60.0f);

// testscene_triangle_1----------------------------------------
    //test_scene.setName("testscene_triangle_1");
    //test_scene.placeSphere(2.0, POINT(-2.5, 0.0, 7.0), COLOR(0.7f, 0.7f, 0.7f)); //big sphere
    //test_scene.placeSphere(0.6, POINT(2.0, 2.0, 6.0), COLOR(0.0f, 0.7f, 0.7f)); //small sphere
    //test_scene.placeTriangle(VECTOR3(1.0, 0.0, 5.0), VECTOR3(-1.0, 0.0, 5.0), VECTOR3(0.0, 1.5, 5.0), VECTOR3(0.0, 0.0, -1.0), COLOR(0.8));
    //test_scene.placeLight(40.0, POINT(-3.0, 2.5, 0.0), COLOR(1.0));
    //test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 60.0f);

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
    //test_scene.placeLight(200.0, POINT(-20.0, 0.0, 8.0), COLOR(1.0)); //set intensity higher in case of black render
    //test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 45.0f);

//testscene_depth-----------------------------------------------
    test_scene.setName("testscene_depth_bug");
    test_scene.placeSphere(2.0, POINT(0.0, 0.0, 10.0), COLOR(0.5f, 1.0f, 0.0f));
    test_scene.placeSphere(0.5, POINT(0.0, 0.0, 6.0), COLOR(0.0f, 0.0f, 0.8f));
    test_scene.placeLight(150.0, POINT(-2.0, 2.0, 0.0), COLOR(1.0));
    test_scene.createCamera(POINT(0.0f), VECTOR3(0.0f, 0.0f, 1.0f), 45.0f);

    float scene_build_time = float(clock() - begin_building_scene) / CLOCKS_PER_SEC;
    const clock_t begin_render = clock();
    unsigned long rays = 1;

    // Create Image
    COLOR** pixels;
    try
    {
      pixels = new COLOR * [IMAGEWIDTH];
      for (int i = 0; i < IMAGEWIDTH; ++i)
      {
        pixels[i] = new COLOR[IMAGEHEIGHT];
      }
    }
    catch (std::bad_alloc& ba)
    {
      std::cerr << "bad_alloc: " << ba.what() << std::endl;
    }

    // Create threads
    std::vector<std::thread> threads;

    std::cout << "------------ Starting Rendering of scene: " << test_scene.name.c_str() << " !----------------" << std::endl;

    for(int j = 0; j < IMAGEHEIGHT; j++)
    {
      threads.push_back(std::thread(shootPrimaryRaySamples, std::ref(pixels), j, std::ref(test_scene), std::ref(rays)));

      if (j % 10 == 0) {
        std::cout << "rendered: " << j << " of " << IMAGEHEIGHT << " rows!" << std::endl;
      }  
    }

    for (auto& th : threads) {
      th.join();
    }

    float render_time = float(clock() - begin_render) / CLOCKS_PER_SEC;
    int min = static_cast<int>(render_time / 60);
    std::cout << "Scene Build Time: " << static_cast<int>(scene_build_time / 60) << " min, " << scene_build_time - (static_cast<int>(scene_build_time / 60) * 60.0) << " seconds" << std::endl;
    std::cout << "Rendertime: " << static_cast<int>(render_time / 60) << " min, " << render_time - (static_cast<int>(render_time / 60) * 60.0) << " seconds" << std::endl;
    std::cout << "Number of rays traced: " << rays << std::endl;
    std::cout << "MRays/s: " << rays / 1000.0 / render_time << std::endl;

    // Save rendered image to disk
    std::string filename = test_scene.getName().append(FILE_EXTENSION);
    if(saveBMP(pixels, filename.c_str()))
    {
        std::cout << "File written to: " << filename.c_str() << std::endl;
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

    errno_t err;
    if ((err = fopen_s(&file_bmp, filename, "wb")) != 0) {
      std::cout << "Error opening file for writing BMP!" << std::endl;
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
