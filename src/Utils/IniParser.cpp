#include "stdafx.h"
#include "IniParser.h"

/* PRIVATE FUNCTIONS ============================================================================================= */

std::string IniParser::search(const std::string identifier, const std::string section)
{
	std::string parsed_string; // Value to be returned.

	std::string string_buff; // Buffer to read lines.
	unsigned line_num = 0;	 // Line counter.

	bool existent_section = false; // Flag to mark if the section exists.

	// Reset stream reading position to beginning.
	fsstream.seekg(0);

	while (std::getline(fsstream, string_buff))
	{
		line_num++;

		// Ignore blank lines.
		if (string_buff.empty())
			continue;

		// Remove all white spaces
		string_buff.erase(remove_if(string_buff.begin(), string_buff.end(), isspace), string_buff.end());

		// If its a section declaration syntax (ex "[Section]")
		if (string_buff.at(0) == '[' && string_buff.at(string_buff.size() - 1) == ']')
		{
			// Compare if it ts the desired section. If not, jump to next line.
			if (string_buff.substr(1, string_buff.size() - 2) != section)
				continue;

			// Set the flag to mark that the section exists in the file.
			existent_section = true;

			// If it is, start searching the identifier.
			while (fsstream >> string_buff)
			{
				// If found the identifier
				if (string_buff == identifier)
				{
					// Read next
					fsstream >> string_buff;

					// If it is not an assignment operator, throw syntax error
					if (string_buff != "=")
						throwSyntaxError(identifier, section, line_num);
					
					// Get the assigned value
					fsstream >> parsed_string;

					// Return the value
					return parsed_string;
						
				}
				// If it is the beginning of another section, break.
				else if (string_buff.at(0) == '[')
					break;
			}
		}
	}

	// Print the correct error message
	if (existent_section)
		ErrorHandler::throwErr("INIPARSER::SEARCH::ERR_DID_NOT_FIND_MATCH: " + identifier + " NOT EXISTENT IN SECTION " + section + "\n	> At file: " + filePath);
	
	else
		ErrorHandler::throwErr("INIPARSER::SEARCH::INEXISTEXT_SECTION: " + section + "\n	> At file: " + filePath);

	return std::string();
}

void IniParser::throwSyntaxError(const std::string identifier, const std::string section, const unsigned line_num)
{
	std::cerr << "[IniParser] (Syntax Error): Expected operator \"=\"" << "\n"
			  << "	> At identifier \"" << identifier << "\"" << "\n"
			  << "	> At section \"" << section << "\" (line " << line_num << ")" << "\n"
			  << "	> At file \"" << filePath << "\"\n";

	exit(EXIT_FAILURE);
}

void IniParser::throwConversionError(const std::string value, const std::string type,
									 const std::string identifier, const std::string section)
{
	std::cerr << "[IniParser] (Type Error): Invalid conversion" << "\n"
			  << "	> value \"" << value << "\" to " << type << "\n"
			  << "	> At identifier \"" << identifier << "\"" << "\n"
			  << "	> At section \"" << section << "\"\n"
			  << "	> At file \"" << filePath << "\"\n";

	exit(EXIT_FAILURE);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

IniParser::IniParser(const std::string file_path)
{
	filePath = file_path;
	preSettedSearchSection = "";

	loadFile(file_path);
}

IniParser::~IniParser() {}

/* FUNCTIONS ===================================================================================================== */

void IniParser::loadFile(const std::string file_path)
{
	std::ifstream ifs(file_path);

	fsstream.clear();

	if (!ifs.is_open())
		ErrorHandler::throwErr("INIPARSER::READ::ERROR_COULD_NOT_LOAD_FILE: " + file_path);

	char c;

	while (ifs >> std::noskipws >> c)
		fsstream << c;

	ifs.close();
}

const std::vector<std::pair<std::string, std::string>> IniParser::getAllKeyValuePairs(const std::string section)
{
	std::vector<std::pair<std::string, std::string>> pairs;

	std::string string_buff; // Buffer to read lines.
	unsigned line_num = 0;	 // Line counter.

	bool existent_section = false; // Flag to mark if the section exists.

	// Reset stream reading position to beginning.
	fsstream.seekg(0);

	while (std::getline(fsstream, string_buff))
	{
		line_num++;

		// Ignore blank lines.
		if (string_buff.empty())
			continue;

		// Remove all white spaces
		string_buff.erase(remove_if(string_buff.begin(), string_buff.end(), isspace), string_buff.end());

		// If its a section declaration syntax (ex "[Section]")
		if (string_buff.at(0) == '[' && string_buff.at(string_buff.size() - 1) == ']')
		{
			// Compare if it ts the desired section. If not, jump to next line.
			if (string_buff.substr(1, string_buff.size() - 2) != section)
				continue;

			// Set the flag to mark that the section exists in the file.
			existent_section = true;

			std::string key;
			std::string value;

			// If it is, start loading keys and values.
			while (fsstream >> string_buff)
			{
				// If at the beginning of another section, return the pairs.
				if (string_buff.at(0) == '[')
					return pairs;

				// Save the key.
				key = string_buff;

				// Read next
				fsstream >> string_buff;

				// If the assignment operator is not correctly used, throw error
				if (string_buff != "=")
					throwSyntaxError(key, section, line_num);

				// Read the value
				fsstream >> string_buff;

				// Save the value
				value = string_buff;

				// Insert a new pair into the vector.
				pairs.push_back(std::pair<std::string, std::string>(key, value));
			}
		}
	}

	// If there is no pairs, check if the section exists. If not, throw and error.
	if (pairs.empty() && !existent_section)
		ErrorHandler::throwErr("INIPARSER::GETALLKEYVALUEPAIRS::INEXISTEXT_SECTION: " + section + "\n	> At file: " + filePath);

	return pairs;
}

const std::string IniParser::getString(const std::string identifier, const std::string section)
{
	std::string value_as_string;

	if (section.empty())
	{
		if (preSettedSearchSection.empty())
			ErrorHandler::throwErr("INIPARSER::GETSTRING::ERR_DID_NOT_PRE_SET_SECTION");

		value_as_string = search(identifier, preSettedSearchSection);
	}
	else
		value_as_string = search(identifier, section);

	return value_as_string;
}

const int IniParser::getInt(const std::string identifier, const std::string section)
{
	std::string value_as_string;
	int parsed_int;

	if (section.empty())
	{
		if (preSettedSearchSection.empty())
			ErrorHandler::throwErr("INIPARSER::GETINT::ERR_DID_NOT_PRE_SET_SECTION");

		value_as_string = search(identifier, preSettedSearchSection);
	}
	else
		value_as_string = search(identifier, section);

	int conversion_sucess = std::sscanf(value_as_string.c_str(), "%d", &parsed_int);

	if (!conversion_sucess)
		throwConversionError(value_as_string, "int", identifier, section);

	return parsed_int;
}

const bool IniParser::getBool(const std::string identifier, const std::string section)
{
	std::string value_as_string;
	bool parsed_bool;

	if (section.empty())
	{
		if (preSettedSearchSection.empty())
			ErrorHandler::throwErr("INIPARSER::GETBOOL::ERR_DID_NOT_PRE_SET_SECTION");

		value_as_string = search(identifier, preSettedSearchSection);
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

const std::string &IniParser::getSearchSection() const
{
	return preSettedSearchSection;
}

/* MODIFIERS ===================================================================================================== */

void IniParser::setSearchSection(const std::string section)
{
	preSettedSearchSection = section;
}
