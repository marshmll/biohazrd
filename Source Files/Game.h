#ifndef GAME_H_
#define GAME_H_

#include "../States/GameState.h"

class Game
{
private:
	/* VARIABLES */
	std::string currentPath;

	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtClock;

	float dt; // Delta Time

	std::stack<State*> states; // A stack with pointers to the game states

	/* INITIALIZERS FUNCTIONS */
	void initVariables();
	void initWindow();
	void initStates();

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
	void endApplication();

	/* ACESSORS */
	const bool isRunning() const;
};

#endif /* GAME_H_ */
