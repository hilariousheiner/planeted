#include "Icosahedron.h"

#include <cmath>

namespace Planeted
{
    Mesh *MakeIcosahedron()
    {
        static const float t = (1.0 + sqrt(5.0)) / 2.0;

        Mesh *result = new Mesh();

        int v00 = result->AddVertex(-1, t, 0);
        int v01 = result->AddVertex( 1, t, 0);
        int v02 = result->AddVertex(-1,-t, 0);
        int v03 = result->AddVertex( 1,-t, 0);

        int v04 = result->AddVertex( 0,-1, t);
        int v05 = result->AddVertex( 0, 1, t);
        int v06 = result->AddVertex( 0,-1,-t);
        int v07 = result->AddVertex( 0, 1,-t);

        int v08 = result->AddVertex( t, 0,-1);
        int v09 = result->AddVertex( t, 0, 1);
        int v10 = result->AddVertex(-t, 0,-1);
        int v11 = result->AddVertex(-t, 0, 1);

        result->AddTriangle(v00, v11, v05);
        result->AddTriangle(v00, v05, v01);
        result->AddTriangle(v00, v01, v07);
        result->AddTriangle(v00, v07, v10);
        result->AddTriangle(v00, v10, v11);

        result->AddTriangle(v01, v05, v09);
        result->AddTriangle(v05, v11, v04);
        result->AddTriangle(v11, v10, v02);
        result->AddTriangle(v10, v07, v06);
        result->AddTriangle(v07, v01, v08);

        result->AddTriangle(v03, v09, v04);
        result->AddTriangle(v03, v04, v02);
        result->AddTriangle(v03, v02, v06);
        result->AddTriangle(v03, v06, v08);
        result->AddTriangle(v03, v08, v09);

        result->AddTriangle(v04, v09, v05);
        result->AddTriangle(v02, v04, v11);
        result->AddTriangle(v06, v02, v10);
        result->AddTriangle(v08, v06, v07);
        result->AddTriangle(v09, v08, v01);

        return result;
    }
}
