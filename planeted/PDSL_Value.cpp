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
        : data(std::move(stringValue))
    {}

    Value::Value(Tuple tupleValue)
        : data(std::move(tupleValue))
    {}

    Value::Value(List listValue)
        : data(std::move(listValue))
    {}

    Value::Value(Mesh meshValue)
        : data(std::move(meshValue))
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

    const Tuple &Value::GetTupleValue() const
    {
        return std::get<Tuple>(this->data);
    }

    const List &Value::GetListValue() const
    {
        return std::get<List>(this->data);
    }

    const Mesh &Value::GetMeshValue() const
    {
        return std::get<Mesh>(this->data);
    }

    Noise *Value::TryGetNoiseValue() const
    {
        if(this->GetValueType() != ValueTypeEnum::Noise)
        {
            return nullptr;
        }
        return std::get<Noise*>(this->data);
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

        if(std::holds_alternative<Tuple>(this->data))
        {
            return ValueTypeEnum::Tuple;
        }
        if(std::holds_alternative<List>(this->data))
        {
            return ValueTypeEnum::List;
        }

        if(std::holds_alternative<Mesh>(this->data))
        {
            return ValueTypeEnum::Mesh;
        }
        if(std::holds_alternative<Noise*>(this->data))
        {
            return ValueTypeEnum::Noise;
        }
        return ValueTypeEnum::Null; // Todo: maybe throw an exception here?
    }

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
            result = "tuple: " + std::get<Tuple>(this->data).ToString();
            break;
        case ValueTypeEnum::List:
            result = "list: " + std::get<List>(this->data).ToString();
            break;

        case ValueTypeEnum::Mesh:
            result = "mesh: " + std::get<Mesh>(this->data).GetName();
            break;
        case ValueTypeEnum::Noise:
            result = "noise";
            break;
        default:
            break;
        }
        return result;
    }

    std::string Value::TypeToString() const
    {
        std::string result = "";

        switch(this->GetValueType())
        {
        case ValueTypeEnum::Int:
            result = "Int";
            break;
        case ValueTypeEnum::Float:
            result = "Float";
            break;
        case ValueTypeEnum::Bool:
            result = "Bool";
            break;
        case ValueTypeEnum::String:
            result = "String";
            break;

        case ValueTypeEnum::Null:
            result = "Null";
            break;
        case ValueTypeEnum::Tuple:
            result = "Tuple";
            break;
        case ValueTypeEnum::List:
            result = "List";
            break;

        case ValueTypeEnum::Mesh:
            result = "Mesh";
            break;
        case ValueTypeEnum::Noise:
            result = "Noise";
            break;
        default:
            break;
        }
        return result;
    }
}
