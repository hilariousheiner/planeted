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
}
