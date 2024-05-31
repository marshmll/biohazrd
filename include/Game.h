/**
 *
 * Game class that acts as the game engine.
 *
 *  Created on: 13 de abr. de 2024
 *      Author: Renan Andrade
 */

#ifndef GAME_H_
#define GAME_H_

#include "MainMenuState.h"

class MainMenuState;

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

	std::stack<State *> states; // A stack with pointers to the game states

	std::map<std::string, sf::Keyboard::Key> acceptedKeys; // Keys the game accepts

	/* INITIALIZERS FUNCTIONS */

	/**
	 * @brief Initializes game variables
	 *
	 * @return void
	 */
	void initVariables();

	/**
	 * @brief Initializes graphics settings from a file.
	 *
	 * @return void
	 */
	void initGraphicsSettings();

	/**
	 * @brief Initializes the RenderWindow
	 * @note -> Creates the window.
	 *
	 * @return void
	 */
	void initWindow();

	/**
	 * @brief Initializes all accepted keys and adds them to a map.
	 * Maps strings to Key enum.
	 *
	 * @return void
	 */
	void initKeys();

	/**
	 * @brief Initializes the data struct members.
	 *
	 * @return void
	 */
	void initStateData();

	/**
	 * @return void
	 *
	 * @brief nitializates states and push them into states stack.
	 */
	void initStates();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */

	/**
	 * @brief Game Class Constructor
	 * @note -> Initializes variables
	 * @note -> Initializes window
	 * @note -> Initializes keys
	 * @note -> Initializes states.
	 */
	Game();

	/**
	 * @brief Frees the window allocated memory and free all
	 * states allocated memory.
	 */
	virtual ~Game();

	/* MAIN FUNCTIONS */

	/**
	 * @brief Keeps updating and rendering the game while
	 * the game is running
	 *
	 * @return void
	 */
	void run();

	/**
	 * @brief Polls SFML events and updates the states
	 * in the game.
	 * @note -> Poll SFML events
	 * @note -> Update the top state in the stack
	 * @note -> Check for ending the top state in the stack
	 * @note -> If there are not more states in the stack, exit the applicaiton.
	 *
	 * @return void
	 */
	void update();

	/**
	 * @brief Renders a frame into the window.
	 *
	 * @return void
	 */
	void render();

	/* AUXILIARY FUNCTIONS */

	/**
	 * @brief Updates the delta time which is taken to update and
	 * render a frame.
	 *
	 * @return void
	 */
	void updateDeltaTime();

	/**
	 * @brief Poll events from the window
	 *
	 * @return void
	 */
	void pollSFMLEvents();

	/**
	 * @brief Closes the window and end application.
	 *
	 * @return void
	 */
	void endApplication();

	/* ACCESSORS */

	/**
	 * @brief Returns if the game is currently running
	 *
	 * @return const bool
	 */
	const bool isRunning() const;
};

#endif /* GAME_H_ */