#ifndef PLANETED_MESH_H
#define PLANETED_MESH_H

#include <string>
#include <vector>
#include "Vector3.h"

namespace Planeted
{
    struct TriangleIndices
    {
        size_t V0;
        size_t V1;
        size_t V2;
    };

    class Mesh
    {
    public:
        Mesh();
        Mesh(std::string name);

        // vertices:
        size_t AddVertex(float x, float y, float z);

        void TranslateVertex(size_t id, const Vector3 &t);

        const Vector3 &GetVertex(size_t id) const;

        size_t VertexCount() const;
        const std::vector<Vector3> &Vertices() const;

        // triangles:
        void AddTriangle(size_t a, size_t b, size_t c);
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
