#ifndef PLANETED_PDSL_PARSER_H
#define PLANETED_PDSL_PARSER_H

#include "PDSL.h"
#include "PDSL_Ast.h"

#include <memory>

namespace Planeted
{
    struct Program
    {
        std::vector<std::unique_ptr<Statement>> statements;
    };

    class Parser
    {
    public:
        Parser(Lexer &lexer);

        Program Parse();

    private:

        std::unique_ptr<Statement> parseStatement();

        std::unique_ptr<ImportStatement> parseImportStatement();

        std::unique_ptr<ReturnStatement> parseReturnStatement();

        std::unique_ptr<AssignmentStatement> parseAssignmentStatement();

        std::unique_ptr<ExpressionStatement> parseExpressionStatement();

        std::unique_ptr<Expression> parseExpression();

        std::unique_ptr<ConstantExpression> parseLiteral();

        std::unique_ptr<CallExpression> parseCallExpression();

        std::unique_ptr<TupleExpression> parseTupleExpression();

        std::unique_ptr<ListExpression> parseListExpression();

        void advance();

        Token expect(TokenTypeEnum tokenType);

        Token current;
        Token next;
        Lexer &lexer;
    };
}
#endif
