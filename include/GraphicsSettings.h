#ifndef GRAPHICSSETTINGS_H_
#define GRAPHICSSETTINGS_H_

class GraphicsSettings
{
public:
	/* VARIABLES */
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	/* CONSTRUCTOR AND DESTRUCTOR */
	GraphicsSettings();
	~GraphicsSettings();

	/* FUNCTIONS */
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};
#endif /* GRAPHICSSETTINGS_H_ */
