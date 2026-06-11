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

    Random::SetNormalizeFBM(false);
    Random::SetStartFrequency(4);
    Random::SetNumberOfOctaves(6);
    Random::SetExponent(10.0f);

    Random::FBMParameters fbmParams;
    Random::NoiseParameters noiseParams;

    NoiseTest3D(fbmParams, noiseParams, Random::NoiseTypeEnum::Value, Random::NoiseStyleEnum::Ridge);

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
    std::cout << "\t A cli tool for procedurally creating 3D models of asteroids, moons and minor planets." << std::endl;
}
