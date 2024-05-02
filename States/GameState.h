#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"
#include "../TileMap/TileMap.h"

class GameState: public State
{
private:
	/* VARIABLES */
	gui::PauseMenu *pauseMenu;

	Player *player;

	sf::Font font;

	TileMap *tileMap;

	/* INITIALIZERS */
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	GameState(StateData *data);
	virtual ~GameState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);

	void updatePauseMenuButtons();
};

#endif /* STATES_GAMESTATE_H_ */
