/*
 * State class that manages generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */
State::State(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys)
{
	/**
	 * @constructor
	 *
	 * Constructs a State instance.
	 * -> Sets this->window to window pointer
	 * -> Sets this->quit to false
	 * -> Sets this->acceptedKeys to acceptedKeys pointer.
	 */

	this->window = window;
	this->quitCurrentState = false;
	this->acceptedKeys = acceptedKeys;
	this->currentPath = std::filesystem::current_path().string();
}

State::~State()
{

}

/* DEFINED VIRTUAL FUNCTIONS */
void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	// std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void State::checkForQuitState()
{
	/**
	 * @return void
	 *
	 * Check for quitting the running state.
	 * -> If yes, sets this->quitTheState to true.
	 */

	if (sf::Keyboard::isKeyPressed(this->keybinds["CLOSE"]))
		this->quitCurrentState = true;
	else
		this->quitCurrentState = false;
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

	return this->quitCurrentState;
}
