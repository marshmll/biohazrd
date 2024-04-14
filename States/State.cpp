/*
 * State class that manages generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */
State::State(sf::RenderWindow *window)
{
	this->window = window;
	this->quit = false;
}

State::~State()
{

}


/* DEFINED VIRTUAL FUNCTIONS */
void State::checkForQuit()
{
	/**
	 * @return void
	 *
	 * Check for quitting the state.
	 * -> If yes, sets this->quit to true.
	 */


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->quit = true;
	}
}


/* ACESSORS */
const bool& State::requestedToQuit() const
{
	/**
	 * @return bool
	 *
	 * Returns this->quit value.
	 * The quit boolean value determines if the state
	 * needs to quit or not.
	 */


	return this->quit;
}
