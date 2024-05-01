#ifndef STATES_EDITORSTATE_H_
#define STATES_EDITORSTATE_H_

#include "State.h"
#include "../Map/TileMap.h"

class State;
class TileMap;

class EditorState: public State
{
private:
	/* VARIABLES */
	sf::Font font;

	gui::PauseMenu *pauseMenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap map;

	/* INITIALIZERS */
	void initVariables();
	void initKeybinds();
	void initFonts();
	void initBackground();
	void initPauseMenu();
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	EditorState(StateData *data);
	virtual ~EditorState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateButtons();
	void updatePauseMenuButtons();

	void renderButtons(sf::RenderTarget &target);
};

#endif /* STATES_EDITORSTATE_H_ */
