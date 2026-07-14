#ifndef PLANETED_PDSL_UTILS_H
#define PLANETED_PDSL_UTILS_H

#include "PDSL_Value.h"

namespace Planeted
{
    void ExpectArgsCount(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtLeast(const std::vector<Value> &args, size_t expected, const std::string functionName);
    void ExpectArgsCountAtMost(const std::vector<Value> &args, size_t expected, const std::string functionName);
}

#endif // PLANETED_PDSL_UTILS_H
