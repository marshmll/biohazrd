#include "stdafx.h"
#include "Parser.h"

std::optional<Token> Parser::current_token()
{
    if (currentPosition < tokens.size())
        return tokens.at(currentPosition);

    return {};
}

std::optional<Token> Parser::consume_token()
{
    ++currentPosition;

    if (currentPosition - 1 < tokens.size())
        return tokens.at(currentPosition - 1);

    return {};
}

const std::optional<std::string> Parser::parse_assignment_expression(const std::string &identifier, const bool in_section)
{
    if (!in_section)
    {
        reset_position();
    }

    while (current_token().has_value())
    {
        std::string expression_literal;

        if (current_token().value().getType() == TokenType::IDENTIFIER)
        {
            if (current_token().value().getSpan().literal == identifier)
            {
                expression_literal.append(current_token().value().getSpan().literal);
                consume_token();

                while (current_token().has_value())
                {
                    expression_literal.append(current_token().value().getSpan().literal);

                    if (current_token().value().getType() == TokenType::ASSIGNMENT)
                    {
                        consume_token();

                        while (current_token().has_value())
                        {
                            if (current_token().value().getType() == TokenType::WHITESPACE)
                            {
                                expression_literal.append(current_token().value().getSpan().literal);
                                consume_token();
                            }
                            else if (current_token().value().getType() == TokenType::NEWLINE ||
                                     current_token().value().getType() == TokenType::SECTION ||
                                     current_token().value().getType() == TokenType::IDENTIFIER ||
                                     current_token().value().getType() == TokenType::ASSIGNMENT ||
                                     current_token().value().getType() == TokenType::UNKOWN ||
                                     current_token().value().getType() == TokenType::END)
                            {
                                expression_literal.append(current_token().value().getSpan().literal);

                                std::cerr << "\033[1;31m[IniParser]: Invalid assignment expression:\033[0m" << "\n"
                                          << "\033[1;33m" << expression_literal << "\033[0m" << "\n";

                                return {};
                            }
                            else
                            {
                                return current_token().value().getValue();
                            }
                        }
                    }
                    else if (current_token().value().getType() == TokenType::WHITESPACE)
                    {
                        consume_token();
                    }
                    else
                    {
                        std::cerr << "\033[1;31m[IniParser]: Akward expression:\033[0m" << "\n"
                                  << "\033[1;33m\"" << expression_literal << "\033[0m" << "\n";

                        return {};
                    }
                }
            }
            else
            {
                consume_token();
            }
        }
        else if (current_token().value().getType() == TokenType::SECTION && in_section)
        {
            return {};
        }
        else
        {
            consume_token();
        }
    }

    return {};
}

const std::vector<std::pair<std::string, std::string>> Parser::parse_identifier_value_pairs()
{
    std::vector<std::pair<std::string, std::string>> pairs;

    for (auto &token : tokens)
    {
        if (token.getType() == TokenType::IDENTIFIER)
        {
            std::pair<std::string, std::string> pair;

            pair.first = token.getValue();

            pair.second = parse_assignment_expression(pair.first).value_or("NULL");

            pairs.push_back(pair);

            consume_token();
        }
    }

    return pairs;
}

const std::vector<std::pair<std::string, std::string>> Parser::parse_identifier_value_pairs(const std::string section)
{
    std::vector<std::pair<std::string, std::string>> pairs;

    while (current_token().has_value())
    {
        Token token = current_token().value();

        if (token.getType() == TokenType::IDENTIFIER)
        {
            std::pair<std::string, std::string> pair;

            pair.first = token.getValue();

            pair.second = parse_assignment_expression(pair.first, true).value_or("NULL");

            pairs.push_back(pair);
        }
        else if (token.getType() == TokenType::SECTION)
        {
            break;
        }

        consume_token();
    }

    return pairs;
}

const bool Parser::seek_section(const std::string section)
{
    reset_position();
    while (current_token().has_value())
    {
        if (current_token().value().getType() == TokenType::SECTION)
        {
            if (current_token().value().getValue() == section)
            {
                consume_token();
                return true;
            }
        }
        consume_token();
    }

    return false;
}

void Parser::set_position(const unsigned short position)
{
    currentPosition = position;
}

void Parser::reset_position()
{
    set_position(0);
}

Parser::Parser() : currentPosition(0)
{
}

Parser::~Parser()
{
}

void Parser::loadTokens(std::vector<Token> &tokens)
{
    this->tokens = tokens;
}

const std::string Parser::getProperty(const std::string section, const std::string identifier)
{
    if (seek_section(section))
    {
        std::optional<std::string> value = parse_assignment_expression(identifier, true);

        if (value.has_value())
        {
            return value.value();
        }
        else
        {
            std::cerr << "\033[1;31m[IniParser]: Inexistent or invalid identifier:\033[0m" << "\n"
                      << "\033[1;33m" << identifier << "\033[0m" << "\n"
                      << "\033[1;31mIn section:\033[0m" << "\n"
                      << "\033[1;33m" << section << "\033[0m" << "\n";

            return std::string();
        }
    }
    else
    {
        std::cerr << "\033[1;31m[IniParser]: Inexistent section:\033[0m" << "\n"
                  << "\033[1;33m" << section << "\033[0m" << "\n";
    }

    return std::string();
}

const std::vector<std::pair<std::string, std::string>> Parser::getAllProperties()
{
    return parse_identifier_value_pairs();
}

const std::vector<std::pair<std::string, std::string>> Parser::getAllProperties(const std::string section)
{
    if (seek_section(section))
        return parse_identifier_value_pairs(section);

    std::cerr << "\033[1;31m[IniParser]: Inexistent section:\033[0m" << "\n"
              << "\033[1;33m" << section << "\033[0m" << "\n";

    return std::vector<std::pair<std::string, std::string>>();
}
