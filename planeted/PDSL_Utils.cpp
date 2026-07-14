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
}
