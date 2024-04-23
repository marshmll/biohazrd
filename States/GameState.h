#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"

class GameState: public State
{
private:
	Player *player;

	/* INITIALIZERS */
	void initKeybinds();
	void initTextures();
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
};

#endif /* STATES_GAMESTATE_H_ */
