#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <vector>
#include <string>
#include "Vector3.h"

namespace Planeted
{
    class Mesh
    {
    private:
        std::vector<Vector3> vertices;
    public:
        Mesh();
        ~Mesh();
        int AddVertex(float x, float y, float z);
        void AddTriangle(int a, int b, int c);
    };
}
#endif
