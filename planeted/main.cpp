#include <iostream>
#include <unistd.h>
#include <getopt.h>
#include <cstdlib>

#include "Vector3.h"
#include "Mesh.h"
#include "POV.h"

using namespace Planeted;

char *filename = nullptr;
bool readargs(int argc, char** argv);

void usage();

int main(int argc, char **argv)
{
    if(readargs(argc, argv) == false)
    {
        usage();
        return EXIT_FAILURE; //error;
    }

    /*
    Mesh mesh;
    Vector3* test = new Vector3(3.141, 0.0, 0.0);

    std::cout << POVR::Vector3ToPOV(test) << std::endl;
    std::cout << POVR::MeshToPOVMesh2(&mesh) << std::endl;
    std::cout << POVR::POVSceneFile(filename) << std::endl;
    */

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
        {NULL, 0, NULL, 0}
    };

    while((c = getopt_long(argc, argv, "f:", longopts, &longindex)) != -1)
    {
        switch(c)
        {
        case 'f':
            filename = optarg;
            result = true;
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
