#include "PDSL_Parser.h"

namespace Planeted
{
    Parser::Parser(Lexer &lexer)
        : lexer(lexer)
    {
        this->next = this->lexer.Next();
        this->advance();
    }

    Program Parser::Parse()
    {
        Program result;

        while(this->current.type != TokenTypeEnum::End)
        {
            result.statements.push_back(this->parseStatement());
        }
        return result;
    }

    std::unique_ptr<Statement> Parser::parseStatement()
    {
        std::unique_ptr<Statement> result;

        if(this->current.type == TokenTypeEnum::Return)
        {
            result = this->parseReturnStatement();
            //ToDo: stop parsing. If not eof => unreachable code detected.
        }
        else
        {
            if(this->current.type == TokenTypeEnum::Import)
            {
                result = this->parseImportStatement();
            }
            else
            {
                if(this->next.type == TokenTypeEnum::Equals)
                {
                    result = this->parseAssignmentStatement();
                }
                else
                {
                    result = this->parseExpressionStatement();
                }
            }
        }
        return result;
    }

    std::unique_ptr<ImportStatement> Parser::parseImportStatement()
    {
        this->expect(TokenTypeEnum::Import);

        std::string path = this->expect(TokenTypeEnum::StringLiteral).lexeme;

        return std::make_unique<ImportStatement>(path);
    }

    std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
    {
        // return
        this->expect(TokenTypeEnum::Return);

        // expression
        std::unique_ptr<Expression> expression = this->parseExpression();

        // ;
        this->expect(TokenTypeEnum::Semicolon);

        return std::make_unique<ReturnStatement>(std::move(expression));
    }

    std::unique_ptr<AssignmentStatement> Parser::parseAssignmentStatement()
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

    std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement()
    {
        std::unique_ptr<Expression> expression = this->parseExpression();

        // ;
        this->expect(TokenTypeEnum::Semicolon);

        return std::make_unique<ExpressionStatement>(std::move(expression));
    }

    std::unique_ptr<Expression> Parser::parseExpression()
    {
        if(this->current.type == TokenTypeEnum::Identifier)
        {
            if(this->next.type == TokenTypeEnum::LParen)
            {
                return this->parseCallExpression();
            }
            std::string identifier = this->current.lexeme;
            this->advance();
            return std::make_unique<VariableExpression>(identifier);
        }
        if(this->current.type == TokenTypeEnum::LParen)
        {
            return this->parseTupleExpression();
        }
        return this->parseLiteral();
    }

    std::unique_ptr<ConstantExpression> Parser::parseLiteral()
    {
        Value result;

        switch(this->current.type)
        {
        case TokenTypeEnum::IntLiteral:
            result = Value(std::stoi(current.lexeme));
            break;
        case TokenTypeEnum::FloatLiteral:
            result = Value(std::stof(current.lexeme));
            break;
        case TokenTypeEnum::BoolLiteral:
            result = Value(current.lexeme == "true");
            break;
        case TokenTypeEnum::StringLiteral:
            result = Value(current.lexeme);
            break;
        case TokenTypeEnum::NullLiteral:
            result = Value::Null();
            break;
        default:
            throw std::runtime_error("Invalid value type: " + TokenTypeToString(this->current.type));
            break;
        }

        this->advance();
        return std::make_unique<ConstantExpression>(result);
    }


    std::unique_ptr<CallExpression> Parser::parseCallExpression()
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
        return std::make_unique<CallExpression>(name, std::move(args));
    }

    std::unique_ptr<TupleExpression> Parser::parseTupleExpression()
    {
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
        return std::make_unique<TupleExpression>(std::move(args));
    }

    void Parser::advance()
    {
        this->current = this->next;
        this->next = this->lexer.Next();
    }

    Token Parser::expect(TokenTypeEnum tokenType)
    {
        if(this->current.type != tokenType)
        {
            throw std::runtime_error("Unexpected token: " + TokenTypeToString(this->current.type) + " (expected " + TokenTypeToString(tokenType) + ")");
        }

        Token result = current;
        this->advance();

        return result;
    }
}
