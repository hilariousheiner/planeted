#ifndef PLANETED_UTILS_H
#define PLANETED_UTILS_H

#include <fstream>
#include <functional>
#include <iostream>
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

    struct filename_t
    {
        std::string base;
        std::string extension;

        std::string ToString()
        {
            return base + "." + extension;
        }
    };

    inline filename_t splitFilename(const std::string &filename)
    {
        filename_t result = {filename, ""};

        std::size_t pos = filename.rfind('.');
        if(pos != std::string::npos)
        {
            result.base = filename.substr(0, pos);
            result.extension = filename.substr(pos + 1);
        }
        return result;
    }

    inline std::ostream &operator<<(std::ostream &os, const filename_t &filename)
    {
        os << filename.base;

        if(!filename.extension.empty())
        {
            os << "." << filename.extension;
        }
        return os;
    }

    inline std::string ReadFile(const std::string &path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error("file not found: " + path);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        return buffer.str();
    }
}
#endif // PLANETED_UTILS_H
