#ifndef GAME_H_
#define GAME_H_

#include "MainMenuState.h"

class Game
{
private:
	/* VARIABLES */
	std::string currentPath;

	StateData data;

	GraphicsSettings gfxSettings;

	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtClock;

	float dt; // Delta Time

	float gridSize;

	std::stack<State*> states; // A stack with pointers to the game states

	std::map<std::string, sf::Keyboard::Key> acceptedKeys; // Keys the game accepts

	/* INITIALIZERS FUNCTIONS */
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
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