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

    void PDSL_Run(const std::string &code, PDSL_Runtime &runtime);
    void PDSL_RunFile(const std::string &filename, PDSL_Runtime &runtime);

    struct PDSL_Runtime
    {
        PDSL_Runtime();

        Value GetVariableValue(const std::string &name) const;
        void SetVariableValue(std::string name, Value value);

        void InstallBuiltinFunction(std::string name, BuiltinFunction fn);
        Value CallFunction(std::string &name, std::vector<Value> &args);

        void DumpEnvironment();

        std::unordered_map<std::string, Value> Environment;
        std::unordered_map<std::string, BuiltinFunction> BuiltinFunctionsTable;

        Value Result;
        bool DebugFlag = false;
    };
}
#endif
