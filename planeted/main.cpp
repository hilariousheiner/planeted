#include <iostream>

#include "Vector3.h"
#include "Mesh.h"
#include "POV.h"

using namespace std;
using namespace Planeted;

int main()
{
    Mesh mesh;
    Vector3* test = new Vector3(3.141, 0.0, 0.0);
    cout << "Hello world!" << endl;
    cout << POVR::Vector3ToPOV(test) << endl;
    cout << POVR::MeshToPOVMesh2(&mesh) << endl;
    cout << POVR::POVSceneFile("model.pov") << endl;
    return 0;
}
