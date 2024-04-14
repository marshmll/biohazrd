#ifndef GAME_H_
#define GAME_H_

#include "State.h"

class Game
{
private:
	/* VARIABLES */
	sf::RenderWindow *window;
	sf::Event event;
	sf::VideoMode videoMode;

	sf::Clock dtClock;

	float dt; // Delta Time

	/* INITIALIZERS FUNCTIONS */
	void initVariables();
	void initWindow();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	Game();
	virtual ~Game();

	/* MAIN FUNCTIONS */
	void run();
	void update();
	void render();

	/* AUXILIARY FUNCTIONS */
	void updateDeltaTime();
	void pollSFMLEvents();

	/* ACESSORS */
	const bool isRunning() const;
};

#endif /* GAME_H_ */
