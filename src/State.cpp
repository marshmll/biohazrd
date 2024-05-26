/*
 * State class that serves as base class for generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */
#include "stdafx.h"
#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */

State::State(StateData *data)
{
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

/* AUXILIARY FUNCTIONS */

const float State::p2pX(const float percent)
{
	if (percent >= 100.f)
		return static_cast<float>(this->data->gfxSettings->resolution.width);
	else if (percent <= 0.f)
		return 0.f;

	return std::floor(static_cast<float>(this->data->gfxSettings->resolution.width) * (percent / 100.f));
}

const float State::p2pY(const float percent)
{
	if (percent >= 100.f)
		return static_cast<float>(this->data->gfxSettings->resolution.height);
	else if (percent <= 0.f)
		return 0.f;

	return std::floor(static_cast<float>(this->data->gfxSettings->resolution.height) * (percent / 100.f));
}

/* DEFINED VIRTUAL FUNCTIONS */

void State::updateMousePositions(sf::View *view)
{
	this->mousePosScreen = sf::Mouse::getPosition();

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	this->mousePosGrid = sf::Vector2i(
		static_cast<int>(this->mousePosView.x) / static_cast<int>(this->data->gridSize),
		static_cast<int>(this->mousePosView.y) / static_cast<int>(this->data->gridSize));

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float &dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}

void State::updateMousetime(const float &dt)
{
	if (this->mousetime < this->mousetimeMax)
		this->mousetime += 100.f * dt;
}

void State::quit()
{
	this->quitState = true;
}

void State::pauseToggle()
{
	this->isPaused = !this->isPaused;
}

void State::pause()
{
	this->isPaused = true;
}

void State::resume()
{
	this->isPaused = false;
}

/* ACESSORS */

const bool &State::hasAskedToQuit() const
{
	return this->quitState;
}

const bool State::hasCompletedKeytimeCicle()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

const bool State::hasCompletedMousetimeCicle(sf::Mouse::Button mouseBtn)
{
	if (this->mousetime >= this->mousetimeMax)
	{
		if (sf::Mouse::isButtonPressed(mouseBtn))
			this->mousetime = 0.f;

		return true;
	}

	return false;
}
