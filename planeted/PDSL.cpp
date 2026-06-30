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
        return PDSL_Load(args[0].ToString(), runtime);
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

    std::string PDSL_Runtime::ResolvePath(const std::string &filename) const
    {
        std::string current;

        if (!FileStack.empty())
        {
            current = FileStack.back();
        }

        // If no current file, treat as working directory case
        if (current.empty())
        {
            return filename;
        }

        // strip file name keep directory
        size_t pos = current.find_last_of("/\\");
        std::string dir = (pos == std::string::npos) ? "" : current.substr(0, pos + 1);

        return NormalizePath(dir + filename);
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
        std::string resolved = runtime.ResolvePath(filename);
        std::cout << "running file: " << resolved << "\n";

        runtime.FileStack.push_back(resolved);

        PDSL_Run(ReadFile(resolved), runtime);

        if(runtime.DebugFlag)
        {
            runtime.DumpEnvironment();
        }

        runtime.FileStack.pop_back();
    }

    Value PDSL_Load(const std::string &filename, PDSL_Runtime &runtime)
    {
        PDSL_Runtime new_runtime;

        PDSL_Lib::Load(new_runtime);

        new_runtime.OutPath = runtime.OutPath;

        PDSL_RunFile(runtime.ResolvePath(filename), new_runtime);

        return new_runtime.Result;
    }
}
