#include "PDSL.h"

#include <memory>

#include "PDSL_Lib.h"
#include "PDSL_Parser.h"

namespace Planeted
{
    static Value builtin_setDebugFlag(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        if(args.size() != 1)
        {
            throw std::runtime_error("setDebugFlag expects one argument.");
        }
        runtime.DebugFlag = args[0].GetBoolValue();
        return Value::Null();
    }
    static Value builtin_log(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        if(args.size() != 1)
        {
            throw std::runtime_error("log expects exactly one argument.");
        }
        std::cout << args[0].ToString() << "\n";
        return Value::Null();
    }
    static Value builtin_load(PDSL_Runtime &runtime, const std::vector<Value> &args)
    {
        if(args.size() != 1)
        {
            throw std::runtime_error("load expects exactly one argument.");
        }
        return PDSL_Load(args[0].ToString());
    }

    PDSL_Runtime::PDSL_Runtime()
    {
        this->InstallBuiltinFunction("setDebugFlag", builtin_setDebugFlag);
        this->InstallBuiltinFunction("log", builtin_log);
        this->InstallBuiltinFunction("load", builtin_load);
    }

    Value PDSL_Runtime::GetVariableValue(const std::string &name) const
    {
        std::unordered_map<std::string, Value>::const_iterator it = this->Environment.find(name);
        if(it == this->Environment.end())
        {
            throw std::runtime_error("Undefined variable: " + name);
        }
        return it->second;
    }
    void PDSL_Runtime::SetVariableValue(std::string name, Value value)
    {
        this->Environment[name] = value;
    }


    void PDSL_Runtime::InstallBuiltinFunction(std::string name, BuiltinFunction fn)
    {
        this->BuiltinFunctionsTable[name] = fn;
    }
    Value PDSL_Runtime::CallFunction(std::string &name, std::vector<Value> &args)
    {
        auto it = this->BuiltinFunctionsTable.find(name);
        if(it == this->BuiltinFunctionsTable.end())
        {
            throw std::runtime_error("Unknown function: " + name);
        }
        return it->second(*this, args);
    }

    void PDSL_Runtime::DumpEnvironment()
    {
        std::cout << "environment: \n";
        for(auto &v : this->Environment)
        {
            std::cout << v.first << "\n";
        }
    }

    static void run(const Program &program, PDSL_Runtime &runtime)
    {
        for(const std::unique_ptr<Statement> &stmt : program.statements)
        {
            stmt->execute(runtime);
        }
    }

    void PDSL_Run(const std::string &code, PDSL_Runtime &runtime)
    {
        Lexer lexer(code);
        Parser parser(lexer);
        Program program = parser.Parse();
        run(program, runtime);
    }

    void PDSL_RunFile(const std::string &filename, PDSL_Runtime &runtime)
    {
        std::cout << "running file: " << filename << "\n";

        PDSL_Run(ReadFile(filename), runtime);

        if(runtime.DebugFlag)
        {
            runtime.DumpEnvironment();
        }
    }

    Value PDSL_Load(const std::string &filename)
    {
        PDSL_Runtime runtime;

        PDSL_Lib::Load(runtime);

        PDSL_RunFile(filename, runtime);

        return runtime.Result;
    }
}
