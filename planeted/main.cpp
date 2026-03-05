#include <iostream>
#include <fstream>
#include <unistd.h>
#include <getopt.h>
#include <cstdlib>

#include "Asteroid.h"
#include "Icosahedron.h"
#include "Vector3.h"
#include "Mesh.h"
#include "POV.h"
#include "OBJ.h"

#include "IcoSphere.h"

using namespace Planeted;

char *filename = nullptr;
bool objOutput = false;

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

    Asteroid *plob = new Asteroid();
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
        meshfile << POVR::MeshToPOVMesh2(mesh);

        std::cout << "Writing scene file...\n";
        std::ofstream scenefile("scene.pov");

        scenefile << POVR::POVSceneFile(filename);
        scenefile.close();
    }
    meshfile.close();

    std::cout << "done." << std::endl;

    delete plob;

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
