/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "GameState.h"

/* INITIALIZERS */
void GameState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own binding to a key.
	 */

	std::ifstream ifs(this->currentPath + "/Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
		{
			this->keybinds[action] = this->acceptedKeys->at(key);
		}
	}

	ifs.close();
}

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
		std::stack<State*> *states) :
		State(window, acceptedKeys, states)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor State(window, acceptedKeys) and
	 * initialize the keybinds for the state.
	 */

	this->initKeybinds();
}

GameState::~GameState()
{

}

/* FUNCTIONS */
void GameState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the GameState.
	 * -> Update mouse positions
	 * -> Checks for updates in the user input.
	 */

	this->updateInput(dt);

	this->player.update(dt); // TEMP

}

void GameState::render(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Renders the game state into a target (window).
	 */

	this->player.render(target); // TEMP

}

void GameState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the user input.
	 * -> Checks for quitting the gamestate.
	 * -> Updates mouse positions.
	 * -> Checks for keybinds and executes its respective
	 *    action.
	 */

	this->checkForQuitState();

	this->updateMousePositions();

	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_UP"]))
	{
		this->player.move(dt, 0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_DOWN"]))
	{
		this->player.move(dt, 0.f, 1.f);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_LEFT"]))
	{
		this->player.move(dt, -1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_RIGHT"]))
	{
		this->player.move(dt, 1.f, 0.f);
	}

}

void GameState::endState()
{
	/**
	 * @return void
	 *
	 * Function executed when the state is being ended.
	 */

	std::cout << "> [GameState.cpp] Ending GameState..." << "\n";
}
