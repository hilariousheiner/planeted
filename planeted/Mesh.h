#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <vector>
#include "Vector3.h"

namespace Planeted
{
    struct TriangleIndices
    {
        int v0;
        int v1;
        int v2;
        int n;
    };

    struct VectorIterator
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

    enum class NormalTypeEnum
    {
        None,
        PerFace,
        PerVertex
    };

    class Mesh
    {
    public:
        Mesh();
        int AddVertex(float x, float y, float z);
        Vector3 *GetVertex(size_t id);

        void AddTriangle(int a, int b, int c);
        void SetTriangles(std::vector<TriangleIndices> tris);

        int VertexCount();
        int TriangleCount();

        VectorIterator Vertices() const;
        VectorIterator Normals() const;
        TriangleIterator Triangles() const;

        void ProjectToUnitSphere();
        void CalculateNormals(NormalTypeEnum normalType);

    private:
        NormalTypeEnum normalType;
        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        std::vector<TriangleIndices> triangles;
    };
}
#endif
