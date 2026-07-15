#ifndef PLANETED_PDSL_UTILS_H
#define PLANETED_PDSL_UTILS_H

#include "PDSL_Value.h"

namespace Planeted
{
    // Argument handling:
    void ExpectArgsCount(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtLeast(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtMost(const std::vector<Value> &args, size_t expected, const std::string functionName);

    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName);
    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName, int defaultValue);

    // Value conversions:
    bool TryAsInt(const Value &value, int &out);

    float ToFloat(const Value &value);
    Mesh *ToMesh(const Value &value);
    TriangleIndices ToTriangle(const Value &value);
    Vector3 ToVector3(const Value &value);
}

#endif // PLANETED_PDSL_UTILS_H
