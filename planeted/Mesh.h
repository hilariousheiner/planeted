#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <vector>
#include "Vector3.h"

namespace Planeted
{
    struct TriangleIndices
    {
        int a, b, c;
    };

    struct VertexIterator
    {
        std::vector<Vector3>::const_iterator _begin;
        std::vector<Vector3>::const_iterator _end;

        std::vector<Vector3>::const_iterator begin() const { return _begin; }
        std::vector<Vector3>::const_iterator end() const { return _end; }
    };

    struct TriangleIterator
    {
        std::vector<TriangleIndices>::const_iterator _begin;
        std::vector<TriangleIndices>::const_iterator _end;

        std::vector<TriangleIndices>::const_iterator begin() const { return _begin; }
        std::vector<TriangleIndices>::const_iterator end() const { return _end; }
    };

    class Mesh
    {
    public:
        int AddVertex(float x, float y, float z);
        Vector3 *GetVertex(size_t id);

        void AddTriangle(int a, int b, int c);
        void SetTriangles(std::vector<TriangleIndices> tris);

        int VertexCount();
        int TriangleCount();

        VertexIterator Vertices() const;
        TriangleIterator Triangles() const;

        void ProjectToUnitSphere();

    private:
        std::vector<Vector3> vertices;
        std::vector<TriangleIndices> triangles;
    };
}
#endif
