#pragma once

#include "TextSpan.h"

enum TokenType
{
    INTEGER,
    STRING,
    SECTION,
    ASSIGNMENT,
    WHITESPACE,
    NEWLINE,
    BOOLEAN,
    IDENTIFIER,
    UNKOWN,
    END,
};

class Token
{
private:
    TokenType type;
    TextSpan span;
    std::string value;

public:
    Token(const TokenType type, const TextSpan span, const std::string value);
    Token(const TokenType type);
    ~Token();

    const TokenType &getType() const;
    const TextSpan &getSpan() const;
    const std::string &getValue() const;

    const std::string getTypeName() const;
};
