#ifndef STATES_MAINMENUSTATE_H_
#define STATES_MAINMENUSTATE_H_

#include "../States/GameState.h"
#include "../States/EditorState.h"
#include "../States/SettingsState.h"

class GameState;
class EditorState;
class SettingsState;

class MainMenuState: public State
{
private:
	/* VARIABLES */
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	/* INITIALIZERS */
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	MainMenuState(StateData *data);
	virtual ~MainMenuState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateButtons();

	void renderButtons(sf::RenderTarget &target);
};

#endif /* STATES_MAINMENUSTATE_H_ */
