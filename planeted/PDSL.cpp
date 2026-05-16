#include "PDSL.h"

#include <memory>

#include "PDSL_Parser.h"

namespace Planeted
{
    void run(const Program &program, PDSL_Runtime &runtime)
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
}
