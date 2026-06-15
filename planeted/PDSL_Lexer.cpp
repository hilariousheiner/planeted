#include "PDSL_Lexer.h"

#include <stdexcept>

namespace Planeted
{
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

        if(c == '"')
        {
            return this->readString();
        }

        this->advance();

        switch(c)
        {
        case '=':
            return {TokenTypeEnum::Equals, "="};
            break;
        case ';':
            return {TokenTypeEnum::Semicolon, ";"};
        case '(':
            return {TokenTypeEnum::LParen, "("};
        case ')':
            return {TokenTypeEnum::RParen, ")"};
        case '[':
            return {TokenTypeEnum::LBrack, "["};
        case ']':
            return {TokenTypeEnum::RBrack, "]"};
        case ',':
            return {TokenTypeEnum::Comma, ","};
        case '-':
            return {TokenTypeEnum::Minus, "-"};
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

            if(this->peek() == '/' && this->peekNext() == '/')
            {
                while(this->peek() != '\n' && this->peek() != '\0')
                {
                    this->advance();
                }
                continue;
            }

            if(this->peek() == '/' && this->peekNext() == '*')
            {
                this->advance(); // /
                this->advance(); // *

                while(true)
                {
                    if(this->peek() == '\0')
                    {
                        throw std::runtime_error("Unterminated block comment.");
                    }

                    if(this->peek() == '*' && this->peekNext() == '/')
                    {
                        this->advance(); // *
                        this->advance(); // /
                        break;
                    }
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

        std::unordered_map<std::string, TokenTypeEnum>::const_iterator it;
        it = keywordDict.find(text);
        if(it != keywordDict.end())
        {
            return {it->second, text};
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
            return {TokenTypeEnum::FloatLiteral, text};
        }
        return {TokenTypeEnum::IntLiteral, text};
    }

    Token Lexer::readString()
    {
        std::string lexeme;

        if(this->peek() == '"')
        {
            this->advance(); // discard initial "

            while(this->peek() != '"')
            {
                if(this->peek() == '\0')
                {
                    throw std::runtime_error("unterminated string literal.");
                }
                lexeme += this->advance();
            }
            this->advance(); // discard final "
        }
        return {TokenTypeEnum::StringLiteral, lexeme};
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
}
