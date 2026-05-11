#ifndef PLANETED_PDSL_H
#define PLANETED_PDSL_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "Utils.h"

/*
 * PDSL = planeted scripting language
 */

namespace Planeted
{
    enum class ValueTypeEnum
    {
        Identifier,
        Int,
        Float,
        Bool
    };

    struct Value
    {
        ValueTypeEnum valueType;

        int IntValue;
        float FloatValue;
        bool BoolValue;
        std::string Identifier;
    };

    struct PDSL_Runtime
    {
        std::unordered_map<std::string, Value> Environment;

        bool debug = false;

        Value GetVariableValue(const std::string &name) const
        {
            std::unordered_map<std::string, Value>::const_iterator it = this->Environment.find(name);
            if(it == this->Environment.end())
            {
                throw std::runtime_error("Undefined variable: " + name);
            }
            return it->second;
        }

        void SetVariableValue(std::string name, Value value)
        {
            this->Environment[name] = value;
        }

        void DumpEnvironment()
        {
            std::cout << "environment: \n";
            for(auto &v : this->Environment)
            {
                std::cout << v.first << "\n";
            }
        }
    };

    void PDSL_Run(const std::string &filename, PDSL_Runtime &runtime);

    inline void PDSL_RunFile(const std::string &filename, PDSL_Runtime &runtime)
    {
        std::cout << "running file: " << filename << "\n";

        PDSL_Run(ReadFile(filename), runtime);

        if(runtime.debug)
        {
            runtime.DumpEnvironment();
        }
    }
}
#endif
