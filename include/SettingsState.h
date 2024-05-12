#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"

class SettingsState: public State
{
private:
	/* VARIABLES */
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	std::map<std::string, gui::DropDownList*> dropDownLists;

	sf::Text optionsText;

	std::vector<sf::VideoMode> videoModes;

	/* INITIALIZERS */
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initGUI();
	void initText();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	SettingsState(StateData *data);
	virtual ~SettingsState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateGUI(const float &dt);

	void renderGUI(sf::RenderTarget &target);

	/* ACCESSORS */
};

#endif /* SETTINGSSTATE_H_ */
