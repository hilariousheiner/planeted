#ifndef PLANETED_PDSL_LEXER_H
#define PLANETED_PDSL_LEXER_H

#include <string>
#include <unordered_map>

#include "PDSL_Token.h"

namespace Planeted
{
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
