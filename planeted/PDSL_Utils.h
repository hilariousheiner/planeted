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

    float GetFloatArg(const std::vector<Value> &args, size_t index, const std::string &functionName);

    std::string GetStringArg(const std::vector<Value> &args, size_t index, const std::string &functionName);

    bool GetBoolArg(const std::vector<Value> &args, size_t index, const std::string &functionName);

    Noise &GetNoiseArg(const std::vector<Value> &args, size_t index, const std::string &functionName);

    // Value conversions:
    bool TryAsInt(const Value &value, int &out);
    bool TryAsFloat(const Value &value, float &out);
    bool TryAsString(const Value &value, std::string &out);
    bool TryAsBool(const Value &value, bool &out);
    bool TryAsVector3(const Value &value, Vector3 &out);
    bool TryAsTriangle(const Value &value, TriangleIndices &out);
    bool TryAsMesh(const Value &value, Mesh &out);

    bool TupleToMesh(const Tuple &t, Mesh &out);
    bool TupleToVector3(const Tuple &t, Vector3 &out);
    bool TupleToTriangle(const Tuple &t, TriangleIndices &out);

    // Arithmetic:
    Value Negate(const Value &value);

    // Get rid of these:
    float ToFloat(const Value &value);
    Mesh *ToMesh(const Value &value);
    TriangleIndices ToTriangle(const Value &value);
    Vector3 ToVector3(const Value &value);
}

#endif // PLANETED_PDSL_UTILS_H
