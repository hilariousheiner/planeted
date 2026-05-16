#ifndef PLANETED_PDSL_TOKEN_H
#define PLANETED_PDSL_TOKEN_H

#include <string>

namespace Planeted
{
    enum class TokenTypeEnum
    {
        Identifier,

        IntLiteral,
        FloatLiteral,
        BoolLiteral,
        StringLiteral,
        NullLiteral,

        Import,

        Equals,
        Semicolon,
        LParen,
        RParen,
        Comma,

        End
    };

    struct Token
    {
        TokenTypeEnum type;
        std::string lexeme;
    };

    inline std::string TokenTypeToString(TokenTypeEnum tokenType)
    {
        std::string result = "unknown token type";
        switch(tokenType)
        {
        case TokenTypeEnum::Identifier:
            result = "Identifier";
            break;
        case TokenTypeEnum::IntLiteral:
            result = "IntLiteral";
            break;
        case TokenTypeEnum::FloatLiteral:
            result = "FloatLiteral";
            break;
        case TokenTypeEnum::BoolLiteral:
            result = "BoolLiteral";
            break;
        case TokenTypeEnum::StringLiteral:
            result = "StringLiteral";
            break;
        case TokenTypeEnum::NullLiteral:
            result = "NullLiteral";
            break;
        case TokenTypeEnum::Import:
            result = "Import";
            break;
        case TokenTypeEnum::Equals:
            result = "Equals";
            break;
        case TokenTypeEnum::Semicolon:
            result = "Semicolon";
            break;
        case TokenTypeEnum::LParen:
            result = "(";
            break;
        case TokenTypeEnum::RParen:
            result = ")";
            break;
        case TokenTypeEnum::Comma:
            result = ",";
            break;
        case TokenTypeEnum::End:
            result = "End";
            break;
        default:
            break;
        }
        return result;
    }
}
#endif
