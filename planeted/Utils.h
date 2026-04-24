#ifndef PLANETED_UTILS_H
#define PLANETED_UTILS_H

#include <functional>
#include <string>
#include <sstream>
#include <vector>

namespace Planeted
{
    template<typename T>
    std::string listToString(const std::vector<T> &l, const std::function<std::string(const T&)> &toStringFunc, const char separator = ',')
    {
        std::stringstream stream;

        if(l.size() >= 1)
        {
            stream << toStringFunc(l[0]);
            for(size_t i = 1; i < l.size(); ++i)
            {
                stream << separator << toStringFunc(l[i]);
            }
        }
        return stream.str();
    }
}
#endif // PLANETED_UTILS_H
