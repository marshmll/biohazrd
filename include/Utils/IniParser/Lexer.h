#pragma once

#include "Token.h"

class Lexer
{
private:
    std::string fileString;
    unsigned fSize;

    unsigned currentPosition;

    std::optional<Token> get_next_token();

    std::optional<char> consume();

    void consume_comment();

    const std::string consume_integer();

    const std::string consume_string();

    const std::string consume_section();

    const std::string consume_identifier();

    const std::string consume_bool();

    std::optional<char> current_char();

    const bool is_comment_start(const char &c);

    const bool is_num_start(const char &c);

    const bool is_string_start(const char &c);

    const bool is_section_start(const char &c);

    const bool is_assignment(const char &c);

    const bool is_whitespace(const char &c);

    const bool is_newline(const char &c);

    const bool is_boolean();

public:
    Lexer();

    ~Lexer();

    std::vector<Token> tokenize(std::stringstream &file_sstream);
};