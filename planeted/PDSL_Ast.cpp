#include "PDSL_Ast.h"

namespace Planeted
{
    // Expressions:

    ConstantExpression::ConstantExpression(Value value)
        : value(value)
    {}

    Value ConstantExpression::eval(PDSL_Runtime &runtime)
    {
        return value;
    }

    VariableExpression::VariableExpression(std::string identifier)
        : Identifier(identifier)
    {}

    Value VariableExpression::eval(PDSL_Runtime &runtime)
    {
        return runtime.GetVariableValue(this->Identifier);
    }

    CallExpression::CallExpression(std::string name, std::vector<std::unique_ptr<Expression>> args)
        : name(name), args(std::move(args))
    {}

    Value CallExpression::eval(PDSL_Runtime &runtime)
    {
        std::vector<Value> evaluatedArgs;

        for(const auto &arg : this->args)
        {
            evaluatedArgs.push_back(arg->eval(runtime));
        }
        return runtime.CallFunction(this->name, evaluatedArgs);
    }

    TupleExpression::TupleExpression(std::vector<std::unique_ptr<Expression>> elements)
        : elements(std::move(elements))
    {}

    Value TupleExpression::eval(PDSL_Runtime &runtime)
    {
        Tuple *tupleValue = new Tuple();

        for(const auto &expr : this->elements)
        {
            tupleValue->elements.push_back(expr->eval(runtime));
        }
        return Value(tupleValue);
    }

    ListExpression::ListExpression(std::vector<std::unique_ptr<Expression>> elements)
        : elements(std::move(elements))
    {}

    Value ListExpression::eval(PDSL_Runtime &runtime)
    {
        List *listValue = new List();

        for(const auto &expr : this->elements)
        {
            listValue->elements.push_back(expr->eval(runtime));
        }
        return Value(listValue);
    }

    UnaryExpression::UnaryExpression(TokenTypeEnum op, std::unique_ptr<Expression> operand)
        : op(op), operand(std::move(operand))
    {}

    Value UnaryExpression::eval(PDSL_Runtime &runtime)
    {
        Value val = this->operand->eval(runtime);
        Value result;

        switch(this->op)
        {
        case TokenTypeEnum::Minus:
            result = val.Negate();
        default:
            throw std::runtime_error("unknown unary operator");
            break;
        }
        return result;
    }

    // Statements:

    AssignmentStatement::AssignmentStatement(std::string name, std::unique_ptr<Expression> expression)
        : name(name), expression(std::move(expression))
    {}

    void AssignmentStatement::execute(PDSL_Runtime &runtime)
    {
        runtime.SetVariableValue(this->name, this->expression->eval(runtime));
    }

    ImportStatement::ImportStatement(std::string path)
        : path(path)
    {}

    void ImportStatement::execute(PDSL_Runtime &runtime)
    {
        PDSL_Run(ReadFile(this->path), runtime);
    }

    ReturnStatement::ReturnStatement(std::unique_ptr<Expression> expression)
        : expression(std::move(expression))
    {}

    void ReturnStatement::execute(PDSL_Runtime &runtime)
    {
        runtime.Result = this->expression->eval(runtime);
    }

    ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expression)
        : expression(std::move(expression))
    {}

    void ExpressionStatement::execute(PDSL_Runtime &runtime)
    {
        this->expression->eval(runtime);
    }
}
