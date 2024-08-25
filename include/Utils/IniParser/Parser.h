#pragma once

#include "Token.h"

class Parser
{
private:
    std::vector<Token> tokens;
    unsigned short currentPosition;

    std::optional<Token> current_token();

    std::optional<Token> consume_token();

    const std::optional<std::string> parse_assignment_expression(const std::string &identifier,
                                                                 const bool in_section = false);

    const std::vector<std::pair<std::string, std::string>> parse_identifier_value_pairs();

    const std::vector<std::pair<std::string, std::string>> parse_identifier_value_pairs(const std::string section);

    const bool seek_section(const std::string section);

    void set_position(const unsigned short position);

    void reset_position();

public:
    Parser();

    ~Parser();

    void loadTokens(std::vector<Token> &tokens);

    const std::string getProperty(const std::string section, const std::string identifier);

    const std::vector<std::pair<std::string, std::string>> getAllProperties();

    const std::vector<std::pair<std::string, std::string>> getAllProperties(const std::string section);
};