#include "stdafx.h"
#include "Lexer.h"

std::optional<Token> Lexer::get_next_token()
{
    if (currentPosition > fSize)
        return {};

    if (currentPosition == fSize)
    {
        ++currentPosition;

        std::string eof_literal = "\0";

        return Token(TokenType::END, TextSpan(0, 0, eof_literal), "\\0");
    }

    while (is_comment_start(current_char().value()))
    {
        consume_comment();
        if (!current_char().has_value())
            return {};
    }

    char c = current_char().value();

    TokenType type = TokenType::UNKOWN;
    std::string value = "";
    const unsigned start = currentPosition;

    if (is_num_start(c))
    {
        type = TokenType::INTEGER;
        value = consume_integer();
    }
    else if (is_string_start(c))
    {
        type = TokenType::STRING;
        value = consume_string();
    }
    else if (is_section_start(c))
    {
        type = TokenType::SECTION;
        value = consume_section();
    }
    else if (is_assignment(c))
    {
        type = TokenType::ASSIGNMENT;
        value = "=";
        consume();
    }
    else if (is_whitespace(c))
    {
        type = TokenType::WHITESPACE;
        value = " ";
        consume();
    }
    else if (is_newline(c))
    {
        type = TokenType::NEWLINE;
        value = "\\n";
        consume();
    }
    else if (is_boolean())
    {
        type = TokenType::BOOLEAN;
        value = consume_bool();
    }
    else
    {
        type = TokenType::IDENTIFIER;
        value = consume_identifier();
    }

    const unsigned end = currentPosition;
    const std::string literal = fileString.substr(start, end - start);
    const TextSpan span = TextSpan(start, end, literal);

    return Token(type, span, value);
}

std::optional<char> Lexer::consume()
{
    std::optional<char> c = current_char();
    ++currentPosition;

    return c;
}

void Lexer::consume_comment()
{
    while (current_char().has_value())
    {
        char c = current_char().value();

        if (is_newline(c))
        {
            consume();
            break;
        }

        consume();
    }
}

const std::string Lexer::consume_integer()
{
    std::string number;

    while (current_char().has_value())
    {
        char c = current_char().value();

        if (isdigit(c))
        {
            consume();
            number.push_back(c);
        }
        else
        {
            break;
        }
    }

    return number;
}

const std::string Lexer::consume_string()
{
    std::string str;
    consume();

    while (current_char().has_value())
    {
        char c = current_char().value();

        if (c == '"')
        {
            consume();
            return str;
        }

        str.push_back(c);
        consume();
    }

    std::cerr << "\033[1;31m[IniParser]: Expected string closing:\033[0m" << "\n"
              << "\033[1;33m\"" << str << "\033[0m" << "\n";

    return str;
}

const std::string Lexer::consume_section()
{
    std::string literal;
    std::string section;

    literal.push_back(consume().value());

    while (current_char().has_value())
    {
        char c = current_char().value();

        if (c == ']')
        {
            literal.push_back(consume().value());

            if (section.size() == 0)
            {
                std::cerr << "\033[1;31m[IniParser]: Empty section:\033[0m" << "\n"
                          << "\033[1;33m" << literal << "\033[0m" << "\n";
            }

            while (is_whitespace(section.at(section.size() - 1)))
                section.erase(section.size() - 1, 1);

            while (is_whitespace(section.at(0)))
                section.erase(0, 1);

            return section;
        }
        else if (is_whitespace(c))
        {
            section.push_back(c);

            literal.push_back(consume().value());
            continue;
        }
        else if (is_section_start(c))
        {
            std::cerr << "\033[1;31m[IniParser]: Missing closing bracket in section:\033[0m" << "\n"
                      << "\033[1;33m" << literal << "\033[0m" << "\n";
        }

        section.push_back(c);
        literal.push_back(consume().value());
    }

    std::cerr << "\033[1;31m[IniParser]: Missing closing bracket in section:\033[0m" << "\n"
              << "\033[1;33m" << literal << "\033[0m" << "\n";

    return section;
}

const std::string Lexer::consume_identifier()
{
    std::string identifier;

    while (current_char().has_value())
    {
        char c = current_char().value();

        if (is_newline(c) || is_whitespace(c) || is_assignment(c) || is_string_start(c))
            break;

        identifier.push_back(c);
        consume();
    }

    return identifier;
}

const std::string Lexer::consume_bool()
{
    std::string boolean;

    while (current_char().has_value())
    {
        char c = current_char().value();

        boolean.push_back(c);

        consume();

        if (boolean == "false")
        {
            break;
        }
        else if (boolean == "true")
        {
            break;
        }
    }

    return boolean;
}

std::optional<char> Lexer::current_char()
{
    if (currentPosition < fSize)
        return fileString.at(currentPosition);

    return {};
}

const bool Lexer::is_comment_start(const char &c)
{
    return c == ';';
}

const bool Lexer::is_num_start(const char &c)
{
    return isdigit(c);
}

const bool Lexer::is_string_start(const char &c)
{
    return c == '"';
}

const bool Lexer::is_section_start(const char &c)
{
    return c == '[';
}

const bool Lexer::is_assignment(const char &c)
{
    return c == '=';
}

const bool Lexer::is_whitespace(const char &c)
{
    return isblank(c);
}

const bool Lexer::is_newline(const char &c)
{
    return c == '\n';
}

const bool Lexer::is_boolean()
{
    return fileString.substr(currentPosition, 5) == "false" ||
           fileString.substr(currentPosition, 4) == "true";
}

Lexer::Lexer()
{
    fileString = "";
    fSize = 0;
    currentPosition = 0;
}

Lexer::~Lexer()
{
}

std::vector<Token> Lexer::tokenize(std::stringstream &file_sstream)
{
    fileString = file_sstream.str();
    fSize = fileString.size();

    std::vector<Token> tokens;

    std::optional<Token> token = get_next_token();

    while (token.has_value())
    {
        tokens.push_back(token.value());

        token = get_next_token();
    }

    return tokens;
}
