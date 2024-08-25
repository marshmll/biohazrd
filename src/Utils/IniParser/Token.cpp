#include "stdafx.h"
#include "Token.h"

Token::Token(const TokenType type, const TextSpan span, const std::string value)
    : type(type), span(span), value(value) {}

Token::Token(const TokenType type) : type(type), span(0, 0, "NULL") {}

Token::~Token() {}

const TokenType &Token::getType() const { return type; }

const TextSpan &Token::getSpan() const { return span; }

const std::string &Token::getValue() const { return value; }

const std::string Token::getTypeName() const
{
    switch (type)
    {
    case INTEGER:
        return "Integer";
    case STRING:
        return "String";
    case SECTION:
        return "Section";
    case ASSIGNMENT:
        return "Assignment";
    case WHITESPACE:
        return "Whitespace";
    case NEWLINE:
        return "Newline";
    case BOOLEAN:
        return "Boolean";
    case IDENTIFIER:
        return "Identifier";
    case UNKOWN:
        return "Unknown";
    case END:
        return "EOF";
    }

    return "ERROR GETTING TYPENAME!";
}
