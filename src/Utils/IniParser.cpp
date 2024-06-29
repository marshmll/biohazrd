#include "stdafx.h"
#include "IniParser.h"

/* PRIVATE FUNCTIONS ============================================================================================= */

string IniParser::search(const string identifier, const string section)
{
    string parsed_str; // Value to be returned.

    string str_buff;       // Buffer to read lines.
    unsigned line_num = 0; // Line counter.

    bool existent_section = false; // Flag to mark if the section exists.

    // Reset stream reading position to beginning.
    fsstream.seekg(0);

    while (getline(fsstream, str_buff))
    {
        line_num++;

        // Ignore blank lines.
        if (str_buff.empty())
            continue;

        // Remove all white spaces
        auto isSpace = [](const unsigned char c)
        { return isspace(c); };

        str_buff.erase(remove_if(str_buff.begin(), str_buff.end(), isSpace), str_buff.end());

        // If it is a comment, skip.
        if (str_buff.at(0) == ';')
            continue;

        // If the size of the buffer is at least at the size of the section + 2 (the two [])
        if (str_buff.size() >= section.size() + 2)
            // Crop the string to containt just the section and the brackets.
            str_buff = str_buff.substr(0, section.size() + 2);

        // If its a section declaration syntax (ex "[Section]")
        if (str_buff.at(0) == '[' && str_buff.at(str_buff.size() - 1) == ']')
        {
            // Compare if it ts the desired section. If not, jump to next line.
            if (str_buff.substr(1, str_buff.size() - 2) != section)
                continue;

            // Set the flag to mark that the section exists in the file.
            existent_section = true;

            // If it is, start searching the identifier.
            while (fsstream >> str_buff)
            {
                // If it is a comment, skip to next line.
                if (str_buff.at(0) == ';')
                {
                    getline(fsstream, str_buff);
                    continue;
                }

                // If found the identifier
                if (str_buff == identifier)
                {
                    // Read next
                    fsstream >> str_buff;

                    // If it is not an assignment operator, throw syntax error
                    if (str_buff != "=")
                        throwSyntaxError(identifier, section, line_num);

                    // Get the assigned value
                    fsstream >> parsed_str;

                    // Return the value
                    return parsed_str;
                }
                // If it is the beginning of another section, break.
                else if (str_buff.at(0) == '[')
                    break;
            }
        }
    }

    // Print the correct error message
    if (existent_section)
        ErrorHandler::throwErr("INIPARSER::SEARCH::ERR_DID_NOT_FIND_MATCH: " + identifier +
                               " NOT EXISTENT IN SECTION " + section + "\n	> At file: " + filePath);

    else
        ErrorHandler::throwErr("INIPARSER::SEARCH::INEXISTEXT_SECTION: " + section +
                               "\n	> At file: " + filePath);

    return string();
}

void IniParser::throwSyntaxError(const string identifier, const string section, const unsigned line_num)
{
    cerr << "[IniParser] (Syntax Error): Expected operator \"=\"" << "\n"
         << "	> At identifier \"" << identifier << "\"" << "\n"
         << "	> At section \"" << section << "\" (line " << line_num << ")" << "\n"
         << "	> At file \"" << filePath << "\"\n";

    exit(EXIT_FAILURE);
}

void IniParser::throwConversionError(const string value, const string type,
                                     const string identifier, const string section)
{
    cerr << "[IniParser] (Type Error): Invalid conversion" << "\n"
         << "	> value \"" << value << "\" to " << type << "\n"
         << "	> At identifier \"" << identifier << "\"" << "\n"
         << "	> At section \"" << section << "\"\n"
         << "	> At file \"" << filePath << "\"\n";

    exit(EXIT_FAILURE);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

IniParser::IniParser(const string file_path)
{
    filePath = file_path;
    sectionPreset = "";

    loadFile(file_path);
}

IniParser::~IniParser() {}

/* FUNCTIONS ===================================================================================================== */

void IniParser::loadFile(const string file_path)
{
    ifstream ifs(file_path);

    fsstream.clear();

    if (!ifs.is_open())
        ErrorHandler::throwErr("INIPARSER::READ::ERROR_COULD_NOT_LOAD_FILE: " + file_path);

    char c;

    while (ifs >> noskipws >> c)
        fsstream << c;

    ifs.close();
}

const vector<pair<string, string>> IniParser::getAllKeyValuePairs(const string section)
{
    string key;
    string value;

    vector<pair<string, string>> pairs;

    string str_buff;       // Buffer to read lines.
    unsigned line_num = 0; // Line counter.

    bool existent_section = false; // Flag to mark if the section exists.

    // Reset stream reading position to beginning.
    fsstream.seekg(0);

    while (getline(fsstream, str_buff))
    {
        line_num++;

        // Ignore blank lines.
        if (str_buff.empty())
            continue;

        // Remove all white spaces
        auto isSpace = [](const unsigned char c)
        { return isspace(c); };
        str_buff.erase(remove_if(str_buff.begin(), str_buff.end(), isSpace), str_buff.end());

        // If it is a comment, skip.
        if (str_buff.at(0) == ';')
            continue;

        // If the size of the buffer is at least at the size of the section + 2 (the two [])
        if (str_buff.size() >= section.size() + 2)
            // Crop the string to containt just the section and the brackets.
            str_buff = str_buff.substr(0, section.size() + 2);

        // If its a section declaration syntax (ex "[Section]")
        if (str_buff.at(0) == '[' && str_buff.at(str_buff.size() - 1) == ']')
        {
            // Compare if it ts the desired section. If not, jump to next line.
            if (str_buff.substr(1, str_buff.size() - 2) != section)
                continue;

            // Set the flag to mark that the section exists in the file.
            existent_section = true;

            // If it is, start loading keys and values.
            while (fsstream >> str_buff)
            {
                // If it is a comment, skip to next line.
                if (str_buff.at(0) == ';')
                {
                    getline(fsstream, str_buff);
                    continue;
                }

                // If at the beginning of another section, return the pairs.
                if (str_buff.at(0) == '[')
                    return pairs;

                // Save the key.
                key = str_buff;

                // Read next
                fsstream >> str_buff;

                // If the assignment operator is not correctly used, throw error
                if (str_buff != "=")
                    throwSyntaxError(key, section, line_num);

                // Read the value
                fsstream >> str_buff;

                // Save the value
                value = str_buff;

                // Insert a new pair into the vector.
                pairs.push_back(pair<string, string>(key, value));
            }
        }
    }

    // If there is no pairs, check if the section exists. If not, throw and error.
    if (pairs.empty())
    {
        if (!existent_section)
            ErrorHandler::throwErr("INIPARSER::GETALLKEYVALUEPAIRS::INEXISTEXT_SECTION: " + section +
                                   "\n	> At file: " + filePath);
        else
            ErrorHandler::throwErr("INIPARSER::GETALLKEYVALUEPAIRS::EMPTY_SECTION: " + section +
                                   "\n	> At file: " + filePath);
    }

    return pairs;
}

const string IniParser::getString(const string identifier, const string section)
{
    string value_as_string;

    if (section.empty())
    {
        if (sectionPreset.empty())
            ErrorHandler::throwErr("INIPARSER::GETSTRING::ERR_DID_NOT_PRE_SET_SECTION");

        value_as_string = search(identifier, sectionPreset);
    }
    else
        value_as_string = search(identifier, section);

    return value_as_string;
}

const int IniParser::getInt(const string identifier, const string section)
{
    string value_as_string;
    int parsed_int;

    if (section.empty())
    {
        if (sectionPreset.empty())
            ErrorHandler::throwErr("INIPARSER::GETINT::ERR_DID_NOT_PRE_SET_SECTION");

        value_as_string = search(identifier, sectionPreset);
    }
    else
        value_as_string = search(identifier, section);

    int conversion_sucess = sscanf(value_as_string.c_str(), "%d", &parsed_int);

    if (!conversion_sucess)
        throwConversionError(value_as_string, "int", identifier, section);

    return parsed_int;
}

const bool IniParser::getBool(const string identifier, const string section)
{
    string value_as_string;
    bool parsed_bool;

    if (section.empty())
    {
        if (sectionPreset.empty())
            ErrorHandler::throwErr("INIPARSER::GETBOOL::ERR_DID_NOT_PRE_SET_SECTION");

        value_as_string = search(identifier, sectionPreset);
    }
    else
        value_as_string = search(identifier, section);

    if (value_as_string == "true")
        parsed_bool = true;

    else if (value_as_string == "false")
        parsed_bool = false;

    else
        throwConversionError(value_as_string, "bool", identifier, section);

    return parsed_bool;
}

/* ACCESSORS ===================================================================================================== */

const string &IniParser::getSectionPreset() const
{
    return sectionPreset;
}

/* MODIFIERS ===================================================================================================== */

void IniParser::setSectionPreset(const string section)
{
    sectionPreset = section;
}
