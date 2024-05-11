#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"
#include "../TileMap/TileMap.h"

class PauseMenu;
class Player;
class TileMap;

class GameState: public State
{
private:
	/* VARIABLES */
	sf::View playerCamera;
	sf::RenderTexture renderBuffer;
	sf::Sprite renderSprite;

	gui::PauseMenu *pauseMenu;

	Player *player;

	sf::Font font;

	TileMap *tileMap;

	/* INITIALIZERS */
	void initBufferedRender();
	void initView();
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

	void renderToBuffer();

	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);

	void updateTileMap(const float &dt);

	void updatePauseMenuButtons();

	void updatePlayerCamera(const float &dt);
};

#endif /* STATES_GAMESTATE_H_ */
