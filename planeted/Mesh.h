#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <vector>
#include <string>
#include "Vector3.h"

namespace Planeted
{
    typedef struct
    {
        int a, b, c;
    }TriangleIndices;

    typedef struct
    {
        std::vector<Vector3>::const_iterator _begin;
        std::vector<Vector3>::const_iterator _end;

        std::vector<Vector3>::const_iterator begin() const { return _begin; }
        std::vector<Vector3>::const_iterator end() const { return _end; }
    }VertexIterator;

    typedef struct
    {
        std::vector<TriangleIndices>::const_iterator _begin;
        std::vector<TriangleIndices>::const_iterator _end;

        std::vector<TriangleIndices>::const_iterator begin() const { return _begin; }
        std::vector<TriangleIndices>::const_iterator end() const { return _end; }
    }TriangleIterator;

    class Mesh
    {
    private:
        std::vector<Vector3> vertices;
        std::vector<TriangleIndices> triangles;

    public:
        Mesh();
        ~Mesh();

        int AddVertex(float x, float y, float z);
        void AddTriangle(int a, int b, int c);

        int VertexCount();
        int TriangleCount();

        VertexIterator Vertices() const;
        TriangleIterator Triangles() const;

        void ProjectToUnitSphere();
    };
}
#endif
