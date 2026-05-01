#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>
#include <cstdlib>

#include "Asteroid.h"
#include "Icosahedron.h"
#include "Vector3.h"
#include "Math.h"
#include "Mesh.h"
#include "POV.h"
#include "PPM.h"
#include "OBJ.h"
#include "Color.h"
#include "PixelMap.h"
#include "SCAD.h"
#include "STL.h"
#include "IcoSphere.h"

using namespace Planeted;

char *filename = nullptr;
bool objOutput = false;
bool stlOutput = false;
bool scadOutput = false;

bool readargs(int argc, char** argv);

void usage();

int main(int argc, char **argv)
{
    if(readargs(argc, argv) == false)
    {
        usage();
        return EXIT_FAILURE; //error;
    }

    std::cout << "Generating mesh..." << std::endl;

    Random::SeedValueNoise(12345);

    Asteroid *plob = new Asteroid("asteroid");
    Mesh& mesh = plob->GenerateMesh();

    std::cout << "done (" << mesh.VertexCount() << " vertices and " << mesh.TriangleCount() << " triangles).\n";

    std::cout << "Writing mesh to \"" << filename << "\"...\n";
    std::ofstream meshfile(filename);

    if(objOutput == true)
    {
        meshfile << OBJ::MeshToOBJ(mesh);
    }
    else
    {
        if(stlOutput == true)
        {
            meshfile << STL::MeshToSTL(mesh);
        }
        else
        {
            if(scadOutput == true)
            {
                meshfile << SCAD::MeshToSCAD(mesh);
            }
            else
            {
                meshfile << POV::MeshToPOVMesh2(mesh);

                std::cout << "Writing scene file...\n";
                std::ofstream scenefile("scene.pov");

                scenefile << POV::POVSceneFile(filename);
                scenefile.close();
            }
        }
    }
    meshfile.close();

    std::cout << "done." << std::endl;

    delete plob;

    //noise test:
    std::cout << "running noise test" << std::endl;

    PixelMap pixMap = PixelMap(512, 512);
    for(int x = 0; x < 512; ++x)
    {
        for(int y = 0; y < 512; ++y)
        {
            std::uint8_t c = ToUint8(SignedToUnitRange(Random::ValueNoise({x * 0.05f, y * 0.05f, 1})));

            pixMap.PutPixel(x, y, {c, c, c});
        }
    }

    std::ofstream ppmfile("test.ppm");

    ppmfile << PPM::PixelMapToPPM(pixMap);
    std::cout << "done." << std::endl;

    return EXIT_SUCCESS;
}

bool readargs(int argc, char **argv)
{
    int c;
    int longindex;
    bool result = false;

    struct option longopts[] =
    {
        {"filename", required_argument, NULL, 'f'},
        {"output", required_argument, NULL, 'o'},
        {NULL, 0, NULL, 0}
    };

    while((c = getopt_long(argc, argv, "f:o:", longopts, &longindex)) != -1)
    {
        switch(c)
        {
        case 'f':
            filename = optarg;
            result = true;
            break;
        case 'o':
            if(std::string(optarg) == "obj")
            {
                objOutput = true;
            }
            else if(std::string(optarg) == "stl")
            {
                stlOutput = true;
            }
            else if(std::string(optarg) == "scad")
            {
                scadOutput = true;
            }
            break;
        default:
            break;
        }
    }
    return result;
}

void usage()
{
    std::cout << "usage: planeted [-f | --filename = <outputfile>]\n\n";
    std::cout << "\t planeted is a tool for procedurally creating and editing models of asteroids, moons and small planets." << std::endl;
}
