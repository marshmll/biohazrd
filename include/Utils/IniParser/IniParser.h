#pragma once

#include "Lexer.h"
#include "Parser.h"

#define NO_SECTION NULL

class IniParser
{
private:
    Lexer *lexer;
    Parser * parser;

    std::stringstream fileSstream;
    std::vector<Token> tokens;

    bool loaded;

    const bool load_sstream(const std::string path);

public:
    IniParser();

    ~IniParser();

    const bool loadFromFile(const std::string path);

    const std::string getProperty(const std::string section, const std::string identifier);

    const std::string getString(const std::string section, const std::string identifier);

    const int getInt(const std::string section, const std::string identifier);

    const bool getBool(const std::string section, const std::string identifier);

    const std::vector<std::pair<std::string, std::string>> getAllProperties();

    const std::vector<std::pair<std::string, std::string>> getAllPropertiesFrom(const std::string section);
};