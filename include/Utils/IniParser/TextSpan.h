#pragma once

class TextSpan
{
public:
    unsigned start;
    unsigned end;
    std::string literal;

    TextSpan(const unsigned start, const unsigned end, const std::string literal);

    ~TextSpan();

};