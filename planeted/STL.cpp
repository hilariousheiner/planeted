#include <iomanip>
#include <sstream>
#include <string.h>

#include "STL.h"

namespace Planeted
{
    namespace STL
    {
        std::string MeshToSTL(Mesh &mesh)
        {
            std::stringstream stream;

            stream << "solid mesh\n";

            stream << "endsolid";

            return stream.str();
        }
    }
}
