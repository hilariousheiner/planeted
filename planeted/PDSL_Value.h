#ifndef PLANETED_PDSL_VALUE_H
#define PLANETED_PDSL_VALUE_H

#include <variant>
#include <vector>

#include "Mesh.h"
#include "Noise.h"

namespace Planeted
{
    enum class ValueTypeEnum
    {
        Int,
        Float,
        Bool,
        String,
        Null,

        Tuple,
        List,

        Mesh,
        Noise
    };

    class Value;

    struct Tuple
    {
        std::vector<Value> elements;

        std::string ToString() const;
    };

    struct List
    {
        std::vector<Value> elements;

        std::string ToString() const;
    };

    class Value
    {
    public:
        Value();
        explicit Value(int intValue);
        explicit Value(float floatValue);
        explicit Value(bool boolValue);
        explicit Value(std::string stringValue);

        explicit Value(Tuple tupleValue);
        explicit Value(List listValue);
        explicit Value(Mesh meshValue);
        explicit Value(Mesh *meshValue) = delete;

        explicit Value(Noise *noiseValue);

        bool IsNull() const;
        static const Value &Null();

        int GetIntValue() const;
        float GetFloatValue() const;
        bool GetBoolValue() const;
        std::string GetStringValue() const;

        const Tuple &GetTupleValue() const;
        Tuple &GetTupleValue();

        const List &GetListValue() const;

        const Mesh &GetMeshValue() const;
        const Mesh *TryGetMeshValue() const;

        Noise &GetNoiseValue() const;
        Noise *TryGetNoiseValue() const;

        ValueTypeEnum GetValueType() const;

        std::string ToString() const;
        std::string TypeToString() const;

    private:
        std::variant<std::monostate, int, float, bool, std::string, Tuple, List, Mesh, Noise*> data;
    };
}
#endif // PLANETED_PDSL_VALUE_H
