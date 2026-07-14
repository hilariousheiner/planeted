#ifndef PLANETED_PDSL_UTILS_H
#define PLANETED_PDSL_UTILS_H

#include "PDSL_Value.h"

namespace Planeted
{
    void ExpectArgsCount(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtLeast(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtMost(const std::vector<Value> &args, size_t expected, const std::string functionName);

    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName);
    int GetIntArg(const std::vector<Value> &args, size_t index, const std::string &functionName, int defaultValue);

    bool TryAsInt(const Value &value, int &out);
}

#endif // PLANETED_PDSL_UTILS_H
