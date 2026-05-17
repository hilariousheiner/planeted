#ifndef PLANETED_PDSL_PARSER_H
#define PLANETED_PDSL_PARSER_H

#include "PDSL.h"

#include <memory>

namespace Planeted
{
    struct Statement
    {
        virtual ~Statement() {}

        virtual void execute(PDSL_Runtime &runtime) = 0;
    };

    struct Expression
    {
        virtual ~Expression() {}

        virtual Value eval(PDSL_Runtime &runtime) = 0;
    };

    struct Program
    {
        std::vector<std::unique_ptr<Statement>> statements;
    };

    struct ConstantExpression : Expression
    {
        Value value;

        ConstantExpression(Value value);

        Value eval(PDSL_Runtime &runtime) override;
    };

    struct VariableExpression : Expression
    {
        std::string Identifier;

        VariableExpression(std::string identifier);

        Value eval(PDSL_Runtime &runtime) override;
    };

    struct CallExpression : Expression
    {
        CallExpression(std::string name, std::vector<std::unique_ptr<Expression>> args);

        Value eval(PDSL_Runtime &runtime) override;

        std::string name;
        std::vector<std::unique_ptr<Expression>> args;
    };

    struct AssignmentStatement : Statement
    {
        AssignmentStatement(std::string name, std::unique_ptr<Expression> expression);

        void execute(PDSL_Runtime &runtime) override;

        std::string name;
        std::unique_ptr<Expression> expression;
    };

    struct ImportStatement : Statement
    {
        ImportStatement(std::string path);

        void execute(PDSL_Runtime &runtime) override;

        std::string path;
    };

    struct ReturnStatement : Statement
    {
        ReturnStatement(std::unique_ptr<Expression> expression);

        void execute(PDSL_Runtime &runtime) override;

        std::unique_ptr<Expression> expression;
    };

    struct FunctionCallStatement : Statement
    {
        FunctionCallStatement(std::string name, std::vector<std::unique_ptr<Expression>> args);

        void execute(PDSL_Runtime &runtime) override;

        std::string name;
        std::vector<std::unique_ptr<Expression>> args;
    };

    struct ExpressionStatement : Statement
    {
        ExpressionStatement(std::unique_ptr<Expression> expression);

        void execute(PDSL_Runtime &runtime) override;

        std::unique_ptr<Expression> expression;
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

        std::unique_ptr<FunctionCallStatement> parseFunctionCallStatement();

        std::unique_ptr<ExpressionStatement> parseExpressionStatement();

        std::unique_ptr<Expression> parseExpression();

        std::unique_ptr<ConstantExpression> parseLiteral();

        std::unique_ptr<CallExpression> parseCallExpression();

        void advance();

        Token expect(TokenTypeEnum tokenType);

        Token current;
        Token next;
        Lexer &lexer;
    };
}
#endif
