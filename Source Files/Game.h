#ifndef GAME_H_
#define GAME_H_

#include "../States/MainMenuState.h"

class Game
{
private:
	/* VARIABLES */
	std::string currentPath;

	sf::RenderWindow *window;
	sf::Event event;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;

	float dt; // Delta Time

	std::stack<State*> states; // A stack with pointers to the game states

	std::map<std::string, sf::Keyboard::Key> acceptedKeys; // Keys the game accepts

	/* INITIALIZERS FUNCTIONS */
	void initVariables();
	void initWindow();
	void initKeys();
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
