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
        Value();
        Value(int intValue);
        Value(float floatValue);
        Value(bool boolValue);
        Value(std::string stringValue);
        Value(Mesh *meshValue);

        bool IsNull() const;
        static const Value &Null();

        int GetIntValue() const;
        float GetFloatValue() const;
        bool GetBoolValue() const;
        std::string GetStringValue() const;
        Mesh *GetMeshValue() const;

        ValueTypeEnum GetValueType() const;

        std::string ToString() const;

    private:
        std::variant<std::monostate, int, float, bool, std::string, Mesh*> data;
    };
}
#endif // PLANETED_PDSL_VALUE_H
