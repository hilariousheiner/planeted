#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <string>
#include <vector>
#include "Vector3.h"

namespace Planeted
{
    struct TriangleIndices
    {
        int V0;
        int V1;
        int V2;
    };

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::string name);

        // vertices:
        int AddVertex(float x, float y, float z);

        Vector3 *GetVertex(size_t id);
        const Vector3 &GetVertex(size_t id) const;

        int VertexCount() const;
        const std::vector<Vector3> &Vertices() const;

        // triangles:
        void AddTriangle(int a, int b, int c);
        void SetTriangles(std::vector<TriangleIndices> tris);

        int TriangleCount() const;
        const std::vector<TriangleIndices> &Triangles() const;

        // normals
        void CalculateNormals();
        Vector3 CalculateNormal(TriangleIndices &tri) const;

        const Vector3 &GetNormal(size_t id) const;
        const std::vector<Vector3> &Normals() const;

        // misc:
        void ProjectToUnitSphere();
        const std::string &GetName() const;
    private:
        std::string name;
        std::vector<Vector3> vertices;
        std::vector<TriangleIndices> triangles;
        std::vector<Vector3> normals;
    };
}
#endif
