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

        int VertexCount() const;
        int TriangleCount() const;

        std::vector<Vector3> Vertices() const;
        std::vector<Vector3> Normals() const;
        std::vector<TriangleIndices> Triangles() const;

        void ProjectToUnitSphere();
        void CalculateNormals(NormalTypeEnum normalType);

        NormalTypeEnum GetNormalType() const;

    private:
        NormalTypeEnum normalType;
        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        std::vector<TriangleIndices> triangles;
    };
}
#endif
