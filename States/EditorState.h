#ifndef STATES_EDITORSTATE_H_
#define STATES_EDITORSTATE_H_

#include "State.h"
#include "../Resource Files/Button.h"

class EditorState: public State
{
private:
	/* VARIABLES */
	sf::Font font;

	std::map<std::string, Button*> buttons;

	/* INITIALIZERS */
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	EditorState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
			std::stack<State*> *states);
	virtual ~EditorState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updateButtons();

	void renderButtons(sf::RenderTarget &target);
};

#endif /* STATES_EDITORSTATE_H_ */
