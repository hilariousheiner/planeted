#include "PDSL_Value.h"
#include "Utils.h"

namespace Planeted
{
    std::string Tuple::ToString() const
    {
        return "(" + listToString<Value>(this->elements, [](const Value &v) {return v.ToString();}) + ")";
    }

    std::string List::ToString() const
    {
        return "[" + listToString<Value>(this->elements, [](const Value &v) {return v.ToString();}) + "]";
    }

    Value::Value()
        : data(std::monostate{})
    {}

    Value::Value(int intValue)
        : data(intValue)
    {}

    Value::Value(float floatValue)
        : data(floatValue)
    {}

    Value::Value(bool boolValue)
        : data(boolValue)
    {}

    Value::Value(std::string stringValue)
        : data(stringValue)
    {}

    Value::Value(Tuple *tupleValue)
        : data(tupleValue)
    {}

    Value::Value(List *listValue)
        : data(listValue)
    {}

    Value::Value(Mesh *meshValue)
        : data(meshValue)
    {}

    Value::Value(Noise *noiseValue)
        : data(noiseValue)
    { }


    bool Value::IsNull() const
    {
        return std::holds_alternative<std::monostate>(this->data);
    }

    const Value &Value::Null()
    {
        static const Value null{};
        return null;
    }

    int Value::GetIntValue() const
    {
        return std::get<int>(this->data);
    }
    float Value::GetFloatValue() const
    {
        return std::get<float>(this->data);
    }
    bool Value::GetBoolValue() const
    {
        return std::get<bool>(this->data);
    }
    std::string Value::GetStringValue() const
    {
        return std::get<std::string>(this->data);
    }

    Tuple &Value::GetTupleValue() const
    {
        return *std::get<Tuple*>(this->data);
    }
    List &Value::GetListValue() const
    {
        return *std::get<List*>(this->data);
    }

    Mesh *Value::GetMeshValue() const
    {
        return std::get<Mesh*>(this->data);
    }
    Noise &Value::GetNoiseValue() const
    {
        return *std::get<Noise*>(this->data);
    }

    ValueTypeEnum Value::GetValueType() const
    {
        if(std::holds_alternative<int>(this->data))
        {
            return ValueTypeEnum::Int;
        }
        if(std::holds_alternative<float>(this->data))
        {
            return ValueTypeEnum::Float;
        }
        if(std::holds_alternative<bool>(this->data))
        {
            return ValueTypeEnum::Bool;
        }

        if(std::holds_alternative<std::string>(this->data))
        {
            return ValueTypeEnum::String;
        }
        if(std::holds_alternative<std::monostate>(this->data))
        {
            return ValueTypeEnum::Null;
        }

        if(std::holds_alternative<Tuple*>(this->data))
        {
            return ValueTypeEnum::Tuple;
        }
        if(std::holds_alternative<List*>(this->data))
        {
            return ValueTypeEnum::List;
        }

        if(std::holds_alternative<Mesh*>(this->data))
        {
            return ValueTypeEnum::Mesh;
        }
        if(std::holds_alternative<Noise*>(this->data))
        {
            return ValueTypeEnum::Noise;
        }
        return ValueTypeEnum::Null; // Todo: maybe throw an exception here?
    }

    // Conversions:

    std::string Value::ToString() const
    {
        std::string result = "";

        switch(this->GetValueType())
        {
        case ValueTypeEnum::Int:
            result = std::to_string(std::get<int>(this->data));
            break;
        case ValueTypeEnum::Float:
            result = std::to_string(std::get<float>(this->data));
            break;
        case ValueTypeEnum::Bool:
            result = std::get<bool>(this->data) == true ? "true" : "false";
            break;
        case ValueTypeEnum::String:
            result = std::get<std::string>(this->data);
            break;

        case ValueTypeEnum::Null:
            result = "null";
            break;
        case ValueTypeEnum::Tuple:
            result = "tuple: " + std::get<Tuple*>(this->data)->ToString();
            break;
        case ValueTypeEnum::List:
            result = "list: " + std::get<List*>(this->data)->ToString();
            break;

        case ValueTypeEnum::Mesh:
            result = "mesh: " + std::get<Mesh*>(this->data)->GetName();
            break;
        case ValueTypeEnum::Noise:
            result = "noise";
            break;
        default:
            break;
        }
        return result;
    }

    // Conversions:
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
