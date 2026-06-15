#ifndef PLANETED_PDSL_AST_H
#define PLANETED_PDSL_AST_H

#include "PDSL.h"

#include <memory>

namespace Planeted
{
    // Expressions:

    struct Expression
    {
        virtual ~Expression() {}

        virtual Value eval(PDSL_Runtime &runtime) = 0;
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

    struct TupleExpression : Expression
    {
        TupleExpression(std::vector<std::unique_ptr<Expression>> elements);

        Value eval(PDSL_Runtime& runtime) override;

        std::vector<std::unique_ptr<Expression>> elements;
    };

    struct ListExpression : Expression
    {
        ListExpression(std::vector<std::unique_ptr<Expression>> elements);

        Value eval(PDSL_Runtime& runtime) override;

        std::vector<std::unique_ptr<Expression>> elements;
    };

    // Statements:

    struct Statement
    {
        virtual ~Statement() {}

        virtual void execute(PDSL_Runtime &runtime) = 0;
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

    struct ExpressionStatement : Statement
    {
        ExpressionStatement(std::unique_ptr<Expression> expression);

        void execute(PDSL_Runtime &runtime) override;

        std::unique_ptr<Expression> expression;
    };
}
#endif // PLANETED_PDSL_AST_H
