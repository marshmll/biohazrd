#ifndef STATES_MAINMENUSTATE_H_
#define STATES_MAINMENUSTATE_H_

#include "../States/GameState.h"
#include "../Resource Files/Button.h"

class MainMenuState: public State
{
private:
	/* VARIABLES */
	sf::RectangleShape background;
	sf::Font font;

	/* INITIALIZERS */
	void initFonts();
	void initKeybinds();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	MainMenuState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys);
	virtual ~MainMenuState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);

	void updateInput(const float &dt);

	void endState();
};

#endif /* STATES_MAINMENUSTATE_H_ */
