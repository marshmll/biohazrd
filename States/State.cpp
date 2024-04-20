/*
 * State class that serves as base class for generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */
State::State(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
		std::stack<State*> *states)
{
	/**
	 * @constructor
	 *
	 * Constructs a State instance.
	 * -> Sets a pointer to the states stack.
	 * -> Sets this->window to window pointer
	 * -> Sets this->quitState to false
	 * -> Sets this->acceptedKeys to acceptedKeys pointer.
	 * -> Sets current path dir.
	 */

	this->states = states;
	this->window = window;
	this->quitState = false;
	this->acceptedKeys = acceptedKeys;
	this->currentPath = std::filesystem::current_path().string();
}

State::~State()
{

}

/* DEFINED VIRTUAL FUNCTIONS */
void State::updateMousePositions()
{
	/**
	 * @return void
	 *
	 * Update mouse postiions relative to:
	 * -> Screen
	 * -> Window
	 * -> View
	 */

	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void State::quit()
{
	/**
	 * @return void
	 *
	 * Sets quit current state to true.
	 * The quit states triggers the state to exit
	 * in Game.cpp [Game::update()]
	 */

	this->quitState = true;
}

/* ACESSORS */
const bool& State::hasAskedToQuit() const
{
	/**
	 * @return bool
	 *
	 * Returns this->quitTheState value.
	 * The quit boolean value determines if the state
	 * needs to quit or not.
	 */

	return this->quitState;
}
