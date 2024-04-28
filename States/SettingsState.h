#ifndef STATES_SETTINGSSTATE_H_
#define STATES_SETTINGSSTATE_H_

#include "State.h"

class SettingsState: public State
{
private:
	/* VARIABLES */
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	gui::DropDownList* ddl;

	/* INITIALIZERS */
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	SettingsState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
			std::stack<State*> *states);
	virtual ~SettingsState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateButtons();

	void renderButtons(sf::RenderTarget &target);

	/* ACCESSORS */
};

#endif /* STATES_SETTINGSSTATE_H_ */
