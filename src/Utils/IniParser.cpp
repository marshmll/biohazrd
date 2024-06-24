#include "stdafx.h"
#include "IniParser.h"

/* PRIVATE FUNCTIONS ============================================================================================= */

std::string IniParser::search(const std::string identifier, const std::string section)
{
	std::string parsed_string; // Value to be returned.

	std::string line_buffer; // Buffer to read lines.
	unsigned line_num = 0;	 // Line counter.

	// Reset stream reading position to beginning.
	fsstream.seekg(0);

	while (std::getline(fsstream, line_buffer))
	{
		line_num++;

		// Ignore blank lines.
		if (line_buffer.empty())
			continue;

		// If its a section declaration syntax (ex "[Section]")
		else if (line_buffer.at(0) == '[' && line_buffer.at(line_buffer.size() - 1) == ']')
		{
			// Remove all white spaces
			line_buffer.erase(remove_if(line_buffer.begin(), line_buffer.end(), isspace), line_buffer.end());

			// Compare if it ts the desired section. If not, jump to next line.
			if (line_buffer.substr(1, line_buffer.size() - 2) != section)
				continue;

			// If it is, start searching the identifier.
			while (fsstream >> line_buffer)
			{
				// If found the identifier
				if (line_buffer == identifier)
				{
					// Read next
					fsstream >> line_buffer;

					// If has an assingment operator
					if (line_buffer == "=")
					{
						// Get the assigned value
						fsstream >> parsed_string;

						// Return the value
						return parsed_string;
					}
					// If not, throw a syntax error.
					else
						throwSyntaxError(identifier, section, line_num);
				}
			}
		}
	}

	// If did not find the matching search parameters, print a warning.
	ErrorHandler::printErr("INIPARSER::SEARCH::WARN_SECTION_OR_IDENTIFIER_NOT_FOUND");

	// Return a blank string.
	return std::string();
}

void IniParser::throwSyntaxError(const std::string identifier, const std::string section, const unsigned line_num)
{
	std::cerr << "[IniParser] (Syntax Error): Expected token \"=\"" << "\n"
			  << "	> At identifier \"" << identifier << "\"" << "\n"
			  << "	> At section \"" << section << "\" (line " << line_num << ")" << "\n";

	exit(EXIT_FAILURE);
}

void IniParser::throwConversionError(const std::string value, const std::string type,
									 const std::string identifier, const std::string section)
{
	std::cerr << "[IniParser] (Type Error): Invalid conversion" << "\n"
			  << "	> value " << value << " to " << type << "\n"
			  << "	> At identifier \"" << identifier << "\"" << "\n"
			  << "	> At section \"" << section << "\n";

	exit(EXIT_FAILURE);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

IniParser::IniParser()
{
	preSettedSearchSection = "";
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

const std::string IniParser::getString(const std::string identifier, const std::string section)
{
	std::string value_as_string;

	if (section.size() == 0)
	{
		if (preSettedSearchSection.size() == 0)
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

	if (section.size() == 0)
	{
		if (preSettedSearchSection.size() == 0)
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

	if (section.size() == 0)
	{
		if (preSettedSearchSection.size() == 0)
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
