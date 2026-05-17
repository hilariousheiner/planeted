#ifndef PLANETED_PDSL_VALUE_H
#define PLANETED_PDSL_VALUE_H

namespace Planeted
{
    enum class ValueTypeEnum
    {
        Int,
        Float,
        Bool,
        String,
        Null
    };

    struct Value
    {
        ValueTypeEnum valueType;

        int IntValue;
        float FloatValue;
        bool BoolValue;
        std::string StringValue;

        Value()
            : valueType(ValueTypeEnum::Null)
        {}

        Value(int intValue)
            : IntValue(intValue), valueType(ValueTypeEnum::Int)
        {}

        Value(float floatValue)
            : FloatValue(floatValue), valueType(ValueTypeEnum::Float)
        {}

        Value(bool boolValue)
            : BoolValue(boolValue), valueType(ValueTypeEnum::Bool)
        {}

        Value(std::string stringValue)
            : StringValue(stringValue), valueType(ValueTypeEnum::String)
        {}

        std::string ToString() const
        {
            std::string result = "";

            switch(this->valueType)
            {
            case ValueTypeEnum::Int:
                result = std::to_string(this->IntValue);
                break;
            case ValueTypeEnum::Float:
                result = std::to_string(this->FloatValue);
                break;
            case ValueTypeEnum::Bool:
                result = this->BoolValue == true ? "true" : "false";
                break;
            case ValueTypeEnum::String:
                result = this->StringValue;
                break;
            case ValueTypeEnum::Null:
                result = "null";
                break;
            default:
                break;
            }
            return result;
        }
    };
}
#endif // PLANETED_PDSL_VALUE_H
