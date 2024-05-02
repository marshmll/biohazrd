/*
 * State class that serves as base class for generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */
#include "../PCH/stdafx.h"
#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */
State::State(StateData *data)
{
	/**
	 * @constructor
	 *
	 * Constructs a State instance.
	 * -> Sets a pointer to the states stack.
	 * -> Sets this->window to window pointer
	 * -> Sets the accepted keys
	 * -> Sets current directory path.
	 * -> Sets this->quitState to false
	 * -> Sets is paused to false
	 * -> Sets keytime and keytimeMax
	 * -> Sets mousetime and mousetimeMax
	 */

	this->data = data;

	this->states = data->states;

	this->gfxSettings = data->gfxSettings;

	this->window = data->window;

	this->acceptedKeys = data->acceptedKeys;

	this->currentPath = std::filesystem::current_path().string();

	this->quitState = false;
	this->isPaused = false;

	this->keytime = 0.f;
	this->keytimeMax = 15.f;

	this->mousetime = 0.f;
	this->mousetimeMax = 10.f;

	this->gridSize = data->gridSize;
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

	this->mousePosGrid = sf::Vector2u(
			static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->data->gridSize),
			static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->data->gridSize));
}

void State::updateKeytime(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the keytime.
	 * The keytime is used for avoiding multiple key presses
	 * at a single press.
	 */

	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}

void State::updateMousetime(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the mousetime.
	 * The mousetime is used for avoiding multiple mouse
	 * clicks at a single click.
	 */

	if (this->mousetime < this->mousetimeMax)
		this->mousetime += 100.f * dt;
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

void State::pause()
{
	/**
	 * @return void
	 *
	 * Pauses the state.
	 * -> Sets isPaused to true.
	 */

	this->isPaused = true;
}

void State::resume()
{
	/**
	 * @return void
	 *
	 * Resumes the state.
	 * -> Sets isPaused to false.
	 */

	this->isPaused = false;
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

const bool State::hasCompletedKeytimeCicle()
{
	/**
	 * @return const bool
	 *
	 * Returns if a keytime cicle has completed.
	 * A keytime cicle means that a defined amount of
	 * time has passed after a key was pressed.
	 * -> Restarts keytime after verification.
	 */

	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const bool State::hasCompletedMousetimeCicle(sf::Mouse::Button mouseBtn)
{
	/**
	 * @return const bool
	 *
	 * Returns if a mousetime cicle has completed.
	 * A mousetime cicle means that a defined amount of
	 * time has passed after a mouse button was pressed.
	 * -> Restarts keytime after verification.
	 */

	if (this->mousetime >= this->mousetimeMax)
	{
		if (sf::Mouse::isButtonPressed(mouseBtn))
			this->mousetime = 0.f;

		return true;
	}

	return false;
}
