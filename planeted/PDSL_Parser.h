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

        ConstantExpression(Value value) : value(value) {}

        Value eval(PDSL_Runtime &runtime) override
        {
            return value;
        }
    };

    struct VariableExpression : Expression
    {
        std::string Identifier;

        VariableExpression(std::string identifier) : Identifier(identifier) {}

        Value eval(PDSL_Runtime &runtime) override
        {
            return runtime.GetVariableValue(this->Identifier);
        }
    };

    struct AssignmentStatement : Statement
    {
        AssignmentStatement(std::string name, std::unique_ptr<Expression> expression) :
            name(name), expression(std::move(expression))
        { }

        virtual void execute(PDSL_Runtime &runtime) override
        {
            runtime.SetVariableValue(this->name, this->expression->eval(runtime));
        }

        std::string name;
        std::unique_ptr<Expression> expression;
    };

    struct ImportStatement : Statement
    {
        ImportStatement(std::string path) :
            path(path) {}

        virtual void execute(PDSL_Runtime &runtime) override
        {
            PDSL_Run(ReadFile(this->path), runtime);
        }

        std::string path;
    };

    struct FunctionCallStatement : Statement
    {
        FunctionCallStatement(std::string name, std::vector<std::unique_ptr<Expression>> args) :
            name(name), args(std::move(args)) {}

        virtual void execute(PDSL_Runtime &runtime) override
        {
            auto it = runtime.BuiltinFunctionsTable.find(this->name);
            if(it == runtime.BuiltinFunctionsTable.end())
            {
                throw std::runtime_error("Unknown function: " + this->name);
            }

            std::vector<Value> evaluatedArgs;

            for(const auto & arg : this->args)
            {
                evaluatedArgs.push_back(arg->eval(runtime));
            }

            it->second(runtime, evaluatedArgs);
        }

        std::string name;
        std::vector<std::unique_ptr<Expression>> args;
    };

    class Parser
    {
    public:
        Parser(Lexer &lexer) :
            lexer(lexer)
        {
            this->next = this->lexer.Next();
            this->advance();
        }

        Program Parse()
        {
            Program result;

            while(this->current.type != TokenTypeEnum::End)
            {
                result.statements.push_back(this->parseStatement());
            }
            return result;
        }

    private:

        std::unique_ptr<Statement> parseStatement()
        {
            std::unique_ptr<Statement> result;

            if(this->current.type == TokenTypeEnum::Import)
            {
                result = this->parseImportStatement();
            }
            else
            {
                if(this->next.type == TokenTypeEnum::LParen)
                {
                    result = this->parseFunctionCallStatement();
                }
                else
                {
                    result = this->parseAssignmentStatement();
                }
            }
            return result;
        }

        std::unique_ptr<ImportStatement> parseImportStatement()
        {
            this->expect(TokenTypeEnum::Import);

            std::string path = this->expect(TokenTypeEnum::StringLiteral).lexeme;

            return std::make_unique<ImportStatement>(path);
        }

        std::unique_ptr<AssignmentStatement> parseAssignmentStatement()
        {
            // identifier
            std::string name = this->expect(TokenTypeEnum::Identifier).lexeme;

            // =
            this->expect(TokenTypeEnum::Equals);

            // expression
            std::unique_ptr<Expression> expression = this->parseExpression();

            // ;
            this->expect(TokenTypeEnum::Semicolon);

            return std::make_unique<AssignmentStatement>(name, std::move(expression));
        }

        std::unique_ptr<FunctionCallStatement> parseFunctionCallStatement()
        {
            // identifier
            std::string name = this->expect(TokenTypeEnum::Identifier).lexeme;

            // parse argument list:
            // (
            this->expect(TokenTypeEnum::LParen);

            std::vector<std::unique_ptr<Expression>> args;

            if(this->current.type != TokenTypeEnum::RParen)
            {
                while(true)
                {
                    args.push_back(this->parseExpression());
                    if(this->current.type == TokenTypeEnum::Comma)
                    {
                        this->advance();
                        continue;
                    }
                    break;
                }
            }
            // )

            this->expect(TokenTypeEnum::RParen);
            // ;
            this->expect(TokenTypeEnum::Semicolon);
            return std::make_unique<FunctionCallStatement>(name, std::move(args));
        }

        std::unique_ptr<Expression> parseExpression()
        {
            if(this->current.type == TokenTypeEnum::Identifier)
            {
                std::string identifier = this->current.lexeme;
                this->advance();
                return std::make_unique<VariableExpression>(identifier);
            }
            return this->parseLiteral();
        }

        std::unique_ptr<ConstantExpression> parseLiteral()
        {
            Value result;

            switch(this->current.type)
            {
            case TokenTypeEnum::IntLiteral:
                result.valueType = ValueTypeEnum::Int;
                result.IntValue = std::stoi(current.lexeme);
                break;
            case TokenTypeEnum::FloatLiteral:
                result.valueType = ValueTypeEnum::Float;
                result.FloatValue = std::stof(current.lexeme);
                break;
            case TokenTypeEnum::BoolLiteral:
                result.valueType = ValueTypeEnum::Bool;
                result.BoolValue = (current.lexeme == "true");
                break;
            case TokenTypeEnum::StringLiteral:
                result.valueType = ValueTypeEnum::String;
                result.StringValue = current.lexeme;
                break;
            default:
                throw std::runtime_error("Invalid value type: " + TokenTypeToString(this->current.type));
                break;
            }

            this->advance();

            return std::make_unique<ConstantExpression>(result);
        }

        void advance()
        {
            this->current = this->next;
            this->next = this->lexer.Next();
        }

        Token expect(TokenTypeEnum tokenType)
        {
            if(this->current.type != tokenType)
            {
                throw std::runtime_error("Unexpected token: " + TokenTypeToString(this->current.type) + " (expected " + TokenTypeToString(tokenType) + ")");
            }

            Token result = current;
            this->advance();

            return result;
        }

        Token current;
        Token next;
        Lexer &lexer;
    };
}
#endif
