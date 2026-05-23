#include "Tests.h"
#include <iostream>
#include <fstream>
#include <string>
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
#include "PDSL.h"
#include "PDSL_Lib.h"
#include "OBJ.h"
#include "Color.h"
#include "PixelMap.h"
#include "SCAD.h"
#include "STL.h"
#include "Utils.h"
#include "IcoSphere.h"

using namespace Planeted;

filename_t outfile;
std::string infile;

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

    PDSL_Runtime runtime;

    PDSL_Lib::Load(runtime);

    PDSL_RunFile(infile, runtime);

    if(!runtime.Result.IsNull())
    {
        std::cout << "program returned: " << runtime.Result.ToString() << "\n";

        Mesh &mesh = *runtime.Result.GetMeshValue();

        std::cout << "done (" << mesh.VertexCount() << " vertices and " << mesh.TriangleCount() << " triangles).\n";

        std::cout << "Writing mesh to \"" << outfile << "\"...\n";
        std::ofstream meshfile(outfile.ToString());

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

                    scenefile << POV::POVSceneFile(outfile.ToString().c_str());
                    scenefile.close();
                }
            }
        }
        meshfile.close();
    }
    else
    {
        std::cout << "no output written.\n";
    }
    std::cout << "done." << std::endl;

    NoiseTest3D(Random::NoiseTypeEnum::Value);

    return EXIT_SUCCESS;
}

bool readargs(int argc, char **argv)
{
    int opt;
    bool ifound = false;
    bool ofound = false;

    while( (opt = getopt(argc, argv, "i:o:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                infile = std::string(optarg);
                ifound = true;
                break;
            case 'o':
                outfile = splitFilename(optarg);
                if(outfile.extension == "obj")
                {
                    objOutput = true;
                }
                else if(outfile.extension== "stl")
                {
                    stlOutput = true;
                }
                else if(outfile.extension == "scad")
                {
                    scadOutput = true;
                }
                ofound = true;
                break;
            default:
                break;
        }
    }
    return ifound && ofound;
}

void usage()
{
    std::cout << "usage: planeted -i infile -o outfile\n\n";
    std::cout << "\t A cli tool for procedurally creating 3D models of asteroids, moons and minor planets." << std::endl;
}
