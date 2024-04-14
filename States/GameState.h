#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"

class GameState: public State
{
private:
	Entity player;

	/* INITIALIZERS */
	void initKeybinds();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	GameState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys);
	virtual ~GameState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);

	void updateInput(const float &dt);

	void endState();
};

#endif /* STATES_GAMESTATE_H_ */
