#ifndef INIPARSER_H_
#define INIPARSER_H_

/**
 * @brief A class that is used to parse data from a .ini file.
 * Note that a .ini file can be divided in sections, each section
 * containing multiple identifiers and its values. Ex:
 * @attention [Section1]
 * @attention
 * @attention Identifier1 = value 1
 * @attention Identifier2 = value 2
 * @attention [Section2]
 * @attention Identifier1 = value 1
 * @attention Identifier2 = value 2
 *
 * @note This parser handles inconsistent spacing.
 */
class IniParser
{
private:
	/* VARIABLES ================================================================================================= */

	string filePath;

	stringstream fsstream;

	string sectionPreset;

	/* PRIVATE FUNCTIONS ======================================================================================== */

	string search(const string identifier, const string section);

	void throwSyntaxError(const string identifier, const string section, const unsigned line_num);

	void throwConversionError(const string value, const string type,
							  const string identifier, const string section);

public:
	/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

	IniParser(const string file_path);

	virtual ~IniParser();

	/* FUNCTIONS ================================================================================================= */

	/**
	 * @brief Loads the entire .ini file into a stringstream.
	 * @param file_path The relative path to the .ini file.
	 *
	 * @note Calls ErrorHandler::throwErr if fails to open the file.
	 *
	 * @return void
	 */
	void loadFile(const string file_path);

	/**
	 * @brief Returns all pairs of (key, value) of a given section.
	 * @param section The section to extract all the identifiers and
	 * their values.
	 *
	 * @return const vector<pair<string, string>>
	 */
	const vector<pair<string, string>> getAllKeyValuePairs(const string section);

	/**
	 * @brief Returns an identifier's value as a string.
	 * @param identifier The identifier's name
	 * @param section The section the identifiers is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const string
	 */
	const string getString(const string identifier, const string section = "");

	/**
	 * @brief Returns an identifier's value as an int.
	 * @param identifier The identifier's name
	 * @param section The section the identifier is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const int
	 */
	const int getInt(const string identifier, const string section = "");

	/**
	 * @brief Returns an identifier's value as an bool.
	 * @param identifier The identifier's name
	 * @param section The section the identifier is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const bool
	 */
	const bool getBool(const string identifier, const string section = "");

	/* ACCESSORS ================================================================================================= */

	/**
	 * @brief Returns the current setted searching section.
	 *
	 * @return const string&
	 */
	const string &getSectionPreset() const;

	/* MODIFIERS ================================================================================================= */

	/**
	 * @brief Sets the searching section. The next readings
	 * can use it if there is no section parameter.
	 * @param section The section name to set.
	 *
	 * @return void
	 */
	void setSectionPreset(const string section);
};

#endif /* INIPARSER_H_ */