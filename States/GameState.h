#ifndef STATES_GAMESTATE_H_
#define STATES_GAMESTATE_H_

#include "State.h"

class GameState: public State
{
private:

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	GameState(sf::RenderWindow *window);
	virtual ~GameState();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);

	void updateKeybinds(const float &dt);

	void endState();
};

#endif /* STATES_GAMESTATE_H_ */
