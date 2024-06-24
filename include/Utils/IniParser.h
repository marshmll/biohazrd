#ifndef INIPARSER_H_
#define INIPARSER_H_

class IniParser
{
private:
	/* VARIABLES ================================================================================================= */

	std::stringstream fsstream;

	std::string preSettedSearchSection;

	/* PRIVATE FUNCTIONS ======================================================================================== */

	std::string search(const std::string identifier, const std::string section);

	void throwSyntaxError(const std::string identifier, const std::string section, const unsigned line_num);

	void throwConversionError(const std::string value, const std::string type,
							  const std::string identifier, const std::string section);

public:
	/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

	IniParser(const std::string file_path);

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
	void loadFile(const std::string file_path);

	const std::vector<std::pair<std::string, std::string>> getAllKeyValuePairs(const std::string section);

	/**
	 * @brief Returns an identifier's value as a std::string.
	 * @param identifier The identifier's name
	 * @param section The section the identifiers is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const std::string
	 */
	const std::string getString(const std::string identifier, const std::string section = "");

	/**
	 * @brief Returns an identifier's value as an int.
	 * @param identifier The identifier's name
	 * @param section The section the identifiers is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const int
	 */
	const int getInt(const std::string identifier, const std::string section = "");

	/**
	 * @brief Returns an identifier's value as an bool.
	 * @param identifier The identifier's name
	 * @param section The section the identifiers is contained in.
	 * May leave empty if already pre-setted a section.
	 *
	 * @return const bool
	 */
	const bool getBool(const std::string identifier, const std::string section = "");

	/* ACCESSORS ================================================================================================= */

	/**
	 * @brief Returns the current setted searching section.
	 *
	 * @return const std::string&
	 */
	const std::string &getSearchSection() const;

	/* MODIFIERS ================================================================================================= */

	/**
	 * @brief Sets the searching section. The next readings
	 * can use it if there is no section parameter.
	 * @param section The section name to set.
	 *
	 * @return void
	 */
	void setSearchSection(const std::string section);
};

#endif /* INIPARSER_H_ */