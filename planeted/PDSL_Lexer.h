#ifndef PLANETED_PDSL_LEXER_H
#define PLANETED_PDSL_LEXER_H

#include "PDSL_Token.h"

namespace Planeted
{
    static const std::unordered_map<std::string, TokenTypeEnum> keywordDict =
    {
        {"true", TokenTypeEnum::BoolLiteral},
        {"false", TokenTypeEnum::BoolLiteral},
        {"import", TokenTypeEnum::Import}
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
        Token readString();

        char peek() const;
        char peekNext() const;
        char advance();

        std::string source;
        size_t pos;
    };
}
#endif
