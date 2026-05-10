#include "PDSL.h"

namespace Planeted
{
    enum class TokenTypeEnum
    {
        Identifier,

        Int,
        Float,
        Bool,

        Keyword,

        Equals,
        Semicolon,

        End
    };

    struct Token
    {
        TokenTypeEnum type;
        std::string lexeme;
    };

    std::string TokenTypeToString(TokenTypeEnum tokenType)
    {
        std::string result = "unknown token type";
        switch(tokenType)
        {
        case TokenTypeEnum::Identifier:
            result = "Identifier";
            break;
        case TokenTypeEnum::Int:
            result = "Int";
            break;
        case TokenTypeEnum::Float:
            result = "Float";
            break;
        case TokenTypeEnum::Bool:
            result = "Bool";
            break;
        case TokenTypeEnum::Keyword:
            result = "Keyword";
            break;
        case TokenTypeEnum::Equals:
            result = "Equals";
            break;
        case TokenTypeEnum::Semicolon:
            result = "Semicolon";
            break;
        case TokenTypeEnum::End:
            result = "End";
            break;
        default:
            break;
        }
        return result;
    }

    static const std::unordered_map<std::string, bool> keywordDict =
    {
        {"true", true},
        {"false", true}
    };

    class Lexer
    {
    public:
        Lexer(const std::string &source);
        Token Next();

    private:
        void readWhitespaceAndComments();
        Token readIdentifier();
        Token readNumber();
        char peek() const;
        char peekNext() const;
        char advance();

        std::string source;
        size_t pos;
    };

    Lexer::Lexer(const std::string &source) :
        source(source), pos(0)
    { }


    Token Lexer::Next()
    {
        this->readWhitespaceAndComments();

        char c = this->peek();

        if(c == '\0')
        {
            return {TokenTypeEnum::End, ""};
        }

        if(std::isalpha(c) || c == '_')
        {
            return this->readIdentifier();
        }

        if(std::isdigit(c))
        {
            return this->readNumber();
        }

        this->advance();

        switch(c)
        {
        case '=':
            return {TokenTypeEnum::Equals, "="};
            break;
        case ';':
            return {TokenTypeEnum::Semicolon, "="};
        default:
            throw std::runtime_error("unexpected character: " + c);
            break;
        }
    }

    void Lexer::readWhitespaceAndComments()
    {
        while(true)
        {
            while(std::isspace(this->peek()))
            {
                this->advance();
            }

            if(this->peek() == '/' || this->peekNext() == '/')
            {
                while(this->peek() != '\n' && this->peek() != '\0')
                {
                    this->advance();
                }
                continue;
            }

            break;
        }
    }

    Token Lexer::readIdentifier()
    {
        std::string text;

        while (std::isalnum(this->peek()) || this->peek() == '_')
        {
            text += this->advance();
        }

        std::unordered_map<std::string, bool>::const_iterator it;
        it = keywordDict.find(text);
        if(it != keywordDict.end())
        {
            return {TokenTypeEnum::Keyword, text};
        }
        return {TokenTypeEnum::Identifier, text};
    }

    Token Lexer::readNumber()
    {
        std::string text;
        bool isFloat = false;

        while(std::isdigit(this->peek()) || this->peek() == '.')
        {
            if(this->peek() == '.')
            {
                if(isFloat)
                {
                    throw std::runtime_error("Invalid float.");
                }
                isFloat = true;
            }
            text += this->advance();
        }

        if(isFloat)
        {
            return {TokenTypeEnum::Float, text};
        }
        return {TokenTypeEnum::Int, text};
    }

    char Lexer::peek() const
    {
        if(this->pos >= this->source.size())
        {
            return '\0';
        }
        return this->source[pos];
    }

    char Lexer::peekNext() const
    {
        size_t next = this->pos + 1;
        if(next >= this->source.size())
        {
            return '\0';
        }
        return this->source[next];
    }

    char Lexer::advance()
    {
        if(this->pos >= this->source.size())
        {
            return '\0';
        }
        return this->source[this->pos++];
    }

    struct Statement
    {
        std::string name;
        Value value;
    };

    struct Program
    {
        std::vector<Statement> statements;
    };

    class Parser
    {
    public:
        Parser(Lexer &lexer) :
            lexer(lexer)
        {
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

        Statement parseStatement()
        {
            Statement result;

            //identifier
            result.name = this->expect(TokenTypeEnum::Identifier).lexeme;

            // =
            this->expect(TokenTypeEnum::Equals);

            // value
            result.value = this->parseValue();

            //;
            this->expect(TokenTypeEnum::Semicolon);

            return result;
        }

        Value parseValue()
        {
            Value result;

            switch(this->current.type)
            {
            case TokenTypeEnum::Identifier:
                result.valueType = ValueTypeEnum::Identifier;
                result.Identifier = current.lexeme;
                break;
            case TokenTypeEnum::Int:
                result.valueType = ValueTypeEnum::Int;
                result.IntValue = std::stoi(current.lexeme);
                break;
            case TokenTypeEnum::Float:
                result.valueType = ValueTypeEnum::Float;
                result.FloatValue = std::stof(current.lexeme);
                break;
            case TokenTypeEnum::Bool:
                result.valueType = ValueTypeEnum::Bool;
                result.BoolValue = (current.lexeme == "true");
                break;
            default:
                throw std::runtime_error("Invalid value type");
            }

            this->advance();

            return result;
        }

        void advance()
        {
            this->current = this->lexer.Next();
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
        Lexer &lexer;
    };

    Value evalValue(const Value &value, PDSL_Runtime &runtime)
    {
        if(value.valueType == ValueTypeEnum::Identifier)
        {
            return runtime.GetVariableValue(value.Identifier);
        }
        return value;
    }

    void run(const Program &program, PDSL_Runtime &runtime)
    {
        for(const Statement &stmt : program.statements)
        {
            Value value = evalValue(stmt.value, runtime);
            runtime.SetVariableValue(stmt.name, value);
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
