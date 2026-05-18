#ifndef PLANETED_PDSL_H
#define PLANETED_PDSL_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "Icosahedron.h"
#include "Utils.h"

#include "PDSL_Lexer.h"
#include "PDSL_Token.h"
#include "PDSL_Value.h"

/*
 * PDSL = planeted scripting language
 */

namespace Planeted
{
    struct PDSL_Runtime;

    using BuiltinFunction = std::function<Value(PDSL_Runtime&, const std::vector<Value>&)>;

    struct PDSL_Runtime
    {
        std::unordered_map<std::string, Value> Environment;
        std::unordered_map<std::string, BuiltinFunction> BuiltinFunctionsTable;

        Value Result;
        bool DebugFlag = false;

        PDSL_Runtime()
        {
            this->BuiltinFunctionsTable["setDebugFlag"] =
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
            {
                if(args.size() != 1)
                {
                    throw std::runtime_error("setDebugFlag expects one argument.");
                }
                runtime.DebugFlag = args[0].GetBoolValue();
                return Value::Null();
            };

            this->BuiltinFunctionsTable["log"] =
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
            {
                if(args.size() != 1)
                {
                    throw std::runtime_error("log expects exactly one argument.");
                }
                std::cout << args[0].ToString() << "\n";
                return Value::Null();
            };

            this->BuiltinFunctionsTable["icosahedron"] =
                [](PDSL_Runtime &runtime, const std::vector<Value> &args)
            {
                if(args.size() != 1)
                {
                    throw std::runtime_error("icosahedron expects exactly one argument.");
                }
                return Value(MakeIcosahedron(args[0].ToString()));
            };
        }

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

        Value CallFunction(std::string &name, std::vector<Value> &args)
        {
            auto it = this->BuiltinFunctionsTable.find(name);
            if(it == this->BuiltinFunctionsTable.end())
            {
                throw std::runtime_error("Unknown function: " + name);
            }

            return it->second(*this, args);
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

        if(runtime.DebugFlag)
        {
            runtime.DumpEnvironment();
        }
    }
}
#endif
