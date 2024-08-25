#include "stdafx.h"
#include "TextSpan.h"

TextSpan::TextSpan(const unsigned start, const unsigned end, const std::string literal)
    : start(start), end(end), literal(literal)
{
}

TextSpan::~TextSpan()
{
}
