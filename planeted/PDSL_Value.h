#ifndef PLANETED_PDSL_VALUE_H
#define PLANETED_PDSL_VALUE_H

#include <variant>

#include "Mesh.h"

namespace Planeted
{
    enum class ValueTypeEnum
    {
        Int,
        Float,
        Bool,
        String,
        Null,
        Mesh
    };

    class Value
    {
    public:
        Value() : data(std::monostate{}) {}
        Value(int intValue) : data(intValue) {}
        Value(float floatValue) : data(floatValue) {}
        Value(bool boolValue) : data(boolValue) {}
        Value(std::string stringValue) : data(stringValue) {}
        Value(Mesh *meshValue) : data(meshValue) {}

        bool IsNull() const
        {
            return std::holds_alternative<std::monostate>(this->data);
        }
        static const Value &Null()
        {
            static const Value null{};
            return null;
        }

        int GetIntValue() const
        {
            return std::get<int>(this->data);
        }
        float GetFloatValue() const
        {
            return std::get<float>(this->data);
        }
        bool GetBoolValue() const
        {
            return std::get<bool>(this->data);
        }
        std::string GetStringValue() const
        {
            return std::get<std::string>(this->data);
        }
        Mesh *GetMeshValue() const
        {
            return std::get<Mesh*>(this->data);
        }

        ValueTypeEnum GetValueType() const
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
            if(std::holds_alternative<Mesh*>(this->data))
            {
                return ValueTypeEnum::Mesh;
            }
            return ValueTypeEnum::Null; // Todo: maybe throw an exception here?
        }

        std::string ToString() const
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
            case ValueTypeEnum::Mesh:
                result = "mesh: " + std::get<Mesh*>(this->data)->GetName();
                break;
            default:
                break;
            }
            return result;
        }

    private:
        std::variant<std::monostate, int, float, bool, std::string, Mesh*> data;
    };
}
#endif // PLANETED_PDSL_VALUE_H
