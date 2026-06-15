#include <fstream>
#include <iostream>
#include <string>

#include "OBJ.h"
#include "POV.h"
#include "PDSL_Lib.h"
#include "SCAD.h"
#include "STL.h"
#include "Tests.h"

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

    if(runtime.Result.GetValueType() == ValueTypeEnum::Mesh)
    {
        Mesh &mesh = *runtime.Result.GetMeshValue();
        std::cout << "created mesh: " << mesh.GetName() << " (" << mesh.VertexCount() << " vertices and " << mesh.TriangleCount() << " triangles)\n";
        std::cout << "writing to \"" << outfile << "\n";
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

                    std::cout << "writing scene file\n";
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
        std::cout << "program did not create an output mesh\n";
    }
    std::cout << "done." << std::endl;

    return EXIT_SUCCESS;
}

bool readargs(int argc, char **argv)
{
    if(argc < 2)
    {
        return false;
    }

    infile = std::string(argv[1]);
    outfile = splitFilename((infile));
    outfile.extension = "obj";
    objOutput = true;

    return true;
}

void usage()
{
    std::cout << "usage: planeted file\n\n";
    std::cout << "A cli tool and scripting language for procedurally creating 3D models of asteroids, moons and minor planets." << std::endl;
}
