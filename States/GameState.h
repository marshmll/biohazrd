#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"
#include "../Map/TileMap.h"

class GameState: public State
{
private:
	/* VARIABLES */
	gui::PauseMenu *pauseMenu;

	Player *player;

	sf::Font font;

	TileMap map;

	/* INITIALIZERS */
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	GameState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
			std::stack<State*> *states);
	virtual ~GameState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);

	void updatePauseMenuButtons();
};

#endif /* STATES_GAMESTATE_H_ */
