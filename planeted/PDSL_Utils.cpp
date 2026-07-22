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

    Mesh *ToMesh(const Value &value)
    {
        if(value.GetValueType() == ValueTypeEnum::Mesh)
        {
            return value.GetMeshValue();
        }
        if(value.GetValueType() == ValueTypeEnum::Tuple)
        {
            const Tuple &t = value.GetTupleValue();
            if(t.elements.size() == 2)
            {
                if(t.elements[0].GetValueType() == ValueTypeEnum::List && t.elements[1].GetValueType() == ValueTypeEnum::List)
                {
                    const List &vertexList = t.elements[0].GetListValue();
                    const List &triangleList = t.elements[1].GetListValue();

                    Mesh *mesh = new Mesh();

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
}
