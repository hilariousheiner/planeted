#include "PDSL_Utils.h"

#include <stdexcept>

namespace Planeted
{
    void ExpectArgsCount(const std::vector<Value> &args, size_t expected, const std::string functionName)
    {
        if(args.size() != expected)
        {
            throw std::runtime_error(functionName + " expects " + std::to_string(expected) + " arguments (" + std::to_string(args.size()) + " given).");
        }
    }

    void ExpectArgsCountAtLeast(const std::vector<Value> &args, size_t expected, const std::string functionName)
    {
        if(args.size() < expected)
        {
            throw std::runtime_error(functionName + " expects at least " + std::to_string(expected) + " arguments (" + std::to_string(args.size()) + " given).");
        }
    }

    void ExpectArgsCountAtMost(const std::vector<Value> &args, size_t expected, const std::string functionName)
    {
        if(args.size() > expected)
        {
            throw std::runtime_error(functionName + " expects at most " + std::to_string(expected) + " arguments (" + std::to_string(args.size()) + " given).");
        }
    }

    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName)
    {
        int result;
        if(!TryAsInt(args[index], result))
        {
            throw std::runtime_error(functionName + ": argument " + std::to_string(index + 1) + " must be an integer.");
        }
        return result;
    }
    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName, int defaultValue)
    {
        if(index >= args.size())
        {
            return defaultValue;
        }
        return GetIntArg(args, index, functionName);
    }

    float GetFloatArg(const std::vector<Value> &args, size_t index, const std::string &functionName)
    {
        float result;
        if(!TryAsFloat(args[index], result))
        {
            throw std::runtime_error(functionName + ": argument " + std::to_string(index + 1) + " must be a float.");
        }
        return result;
    }

    std::string GetStringArg(const std::vector<Value> &args, size_t index, const std::string &functionName)
    {
        std::string result;
        if(!TryAsString(args[index], result))
        {
            throw std::runtime_error(functionName + ": argument " + std::to_string(index + 1) + " must be a string.");
        }
        return result;
    }

    bool GetBoolArg(const std::vector<Value> &args, size_t index, const std::string &functionName)
    {
        bool result;
        if(!TryAsBool(args[index], result))
        {
            throw std::runtime_error(functionName + ": argument " + std::to_string(index + 1) + " must be a bool.");
        }
        return result;
    }

    Noise &GetNoiseArg(const std::vector<Value> &args, size_t index, const std::string &functionName)
    {
        Noise *result = args[index].TryGetNoiseValue();
        if(result == nullptr)
        {
            throw std::runtime_error(functionName + ": argument " + std::to_string(index + 1) + " must be a noise.");
        }
        return *result;
    }

    // Value conversions:
    bool TryAsInt(const Value &value, int &out)
    {
        bool result = false;

        switch(value.GetValueType())
        {
        case ValueTypeEnum::Int:
            out = value.GetIntValue();
            result = true;
            break;
        case ValueTypeEnum::Float:
            out = static_cast<int>(value.GetFloatValue());
            result = true;
            break;
        default:
            break;
        }
        return result;
    }
    bool TryAsFloat(const Value &value, float &out)
    {
        bool result = false;

        switch(value.GetValueType())
        {
        case ValueTypeEnum::Float:
            out = value.GetFloatValue();
            result = true;
            break;
        case ValueTypeEnum::Int:
            out = static_cast<float>(value.GetIntValue());
            result = true;
            break;
        default:
            break;
        }
        return result;
    }

    bool TryAsString(const Value &value, std::string &out)
    {
        bool result = false;

        if(value.GetValueType() == ValueTypeEnum::String)
        {
            out = value.GetStringValue();
            result = true;
        }
        return result;
    }

    bool TryAsBool(const Value &value, bool &out)
    {
        bool result = false;

        if(value.GetValueType() == ValueTypeEnum::Bool)
        {
            out = value.GetBoolValue();
            result = true;
        }
        return result;
    }

    bool TryAsVector3(const Value &value, Vector3 &out)
    {
        bool result = false;

        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            if(TupleToVector3(value.GetTupleValue(), out))
            {
                result = true;
            }
        }
        return result;
    }

    bool TryAsTriangle(const Value &value, TriangleIndices &out)
    {
        bool result = false;
        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            if(TupleToTriangle(value.GetTupleValue(), out))
            {
                result = true;
            }
        }
        return result;
    }

    bool TryAsMesh(const Value &value, Mesh &out)
    {
        bool result = false;
        if(value.GetValueType() == ValueTypeEnum::Mesh)
        {
            out = value.GetMeshValue();
            result = true;
        }
        else
        {
            if(value.GetValueType() == ValueTypeEnum::Tuple)
            {
                if(TupleToMesh(value.GetTupleValue(), out) == true)
                {
                    result = true;
                }
            }
        }
        return result;
    }

    bool TupleToMesh(const Tuple &t, Mesh &out)
    {
        if(t.elements.size() == 2)
        {
            if(t.elements[0].GetValueType() == ValueTypeEnum::List && t.elements[1].GetValueType() == ValueTypeEnum::List)
            {
                const List &vertexList = t.elements[0].GetListValue();
                const List &triangleList = t.elements[1].GetListValue();

                Mesh *mesh = new Mesh();

                for(const Value &v : vertexList.elements)
                {
                    Vector3 vertex;
                    if(TryAsVector3(v, vertex))
                    {
                        mesh->AddVertex(vertex.X, vertex.Y, vertex.Z);
                    }
                    else
                    {
                        // ToDo: error message
                        return false;
                    }
                }
                for(const Value &val : triangleList.elements)
                {
                    TriangleIndices triangle;
                    if(TryAsTriangle(val, triangle))
                    {
                        mesh->AddTriangle(triangle.V0, triangle.V1, triangle.V2);
                    }
                    else
                    {
                        // ToDo: error message
                        return false;
                    }
                }
                out = *mesh;
                return true;
            }
        }
        // ToDo: error message: Mesh literal must be pair of lists
        return false;
    }

    bool TupleToVector3(const Tuple &t, Vector3 &out)
    {
        bool result = false;
        if(t.elements.size() == 3)
        {
            float x, y, z;
            if(TryAsFloat(t.elements[0], x) && TryAsFloat(t.elements[1], y) && TryAsFloat(t.elements[2], z))
            {
                out = Vector3{x,y,z};
                result = true;
            }
        }
        return result;
    }
    bool TupleToTriangle(const Tuple &t, TriangleIndices &out)
    {
        bool result = false;
        if(t.elements.size() == 3)
        {
            int v0, v1, v2;
            if(TryAsInt(t.elements[0], v0) && TryAsInt(t.elements[1], v1) && TryAsInt(t.elements[2], v2))
            {
                out = TriangleIndices
                {
                    static_cast<size_t>(v0),
                    static_cast<size_t>(v1),
                    static_cast<size_t>(v2)
                };
                result = true;
            }
        }
        return result;
    }

    // Arithmetic:
    Value Negate(const Value &value)
    {
        Value result;

        switch(value.GetValueType())
        {
        case ValueTypeEnum::Float:
            result = -(value.GetFloatValue());
            break;
        case ValueTypeEnum::Int:
            result = -(value.GetIntValue());
            break;
        default:
            throw std::runtime_error("cannot negate value.");
            break;
        }
        return result;
    }


    // Get rid of these:
    Mesh *ToMesh(const Value &value)
    {
        Mesh *mesh = value.TryGetMeshValue();
        if(mesh != nullptr)
        {
            return mesh;
        }

        /*
        if(value.GetValueType() == ValueTypeEnum::Mesh)
        {
            return value.GetMeshValue();
        }
        */

        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            const Tuple &t = value.GetTupleValue();
            if(t.elements.size() == 2)
            {
                if(t.elements[0].GetValueType() == ValueTypeEnum::List && t.elements[1].GetValueType() == ValueTypeEnum::List)
                {
                    const List &vertexList = t.elements[0].GetListValue();
                    const List &triangleList = t.elements[1].GetListValue();

                    mesh = new Mesh();

                    for(const Value &v : vertexList.elements)
                    {
                        Vector3 vertex = ToVector3(v);
                        mesh->AddVertex(vertex.X, vertex.Y, vertex.Z);
                    }
                    for(const Value &t : triangleList.elements)
                    {
                        TriangleIndices tri = ToTriangle(t);
                        mesh->AddTriangle(tri.V0, tri.V1, tri.V2);
                    }
                    return mesh;
                }
            }
        }
        throw std::runtime_error("mesh must be a pair (vertexList, triangleList).");
    }

    float ToFloat(const Value &value)
    {
        float result;
        switch(value.GetValueType())
        {
        case ValueTypeEnum::Int:
            result = static_cast<float>(value.GetIntValue());
            break;
        case ValueTypeEnum::Float:
            result = value.GetFloatValue();
            break;
        default:
            throw std::runtime_error("cannot convert value to float.");
            break;
        }
        return result;
    }

    TriangleIndices ToTriangle(const Value &value)
    {
        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            const Tuple &t = value.GetTupleValue();

            if(t.elements.size() != 3)
            {
                throw std::runtime_error("triangle tuple must have 3 elements.");
            }

            return TriangleIndices
            {
                static_cast<size_t>(t.elements[0].GetIntValue()),
                static_cast<size_t>(t.elements[1].GetIntValue()),
                static_cast<size_t>(t.elements[2].GetIntValue())
            };
        }
        throw std::runtime_error("triangle must be an integer tuple.");
    }

    Vector3 ToVector3(const Value &value)
    {
        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            const Tuple &t = value.GetTupleValue();

            if(t.elements.size() != 3)
            {
                throw std::runtime_error("vector must have 3 elements.");
            }
            return Vector3(ToFloat(t.elements[0]), ToFloat(t.elements[1]), ToFloat(t.elements[2]));
        }
        throw std::runtime_error("vector must be a float tuple.");
    }
}
