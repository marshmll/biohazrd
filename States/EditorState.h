#ifndef STATES_EDITORSTATE_H_
#define STATES_EDITORSTATE_H_

#include "State.h"
#include "../TileMap/TileMap.h"

class State;
class TileMap;

class EditorState: public State
{
private:
	/* VARIABLES */
	sf::Font font;

	sf::Text cursorText;

	gui::PauseMenu *pauseMenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap *tileMap;

	sf::RectangleShape sidebar;

	sf::RectangleShape selectorRect;

	sf::IntRect textureRect;

	gui::TextureSelector *textureSelector;

	/* INITIALIZERS */
	void initVariables();
	void initKeybinds();
	void initFonts();
	void initText();
	void initPauseMenu();
	void initButtons();
	void initTileMap();
	void initGUI();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	EditorState(StateData *data);
	virtual ~EditorState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateEditorInput(const float &dt);
	void updateButtons();
	void updatePauseMenuButtons();
	void updateGUI(const float &dt);

	void renderButtons(sf::RenderTarget &target);
	void renderGUI(sf::RenderTarget &target);
};

#endif /* STATES_EDITORSTATE_H_ */
