/*
 * State class that serves as base class for generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */
#include "stdafx.h"
#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR */

State::State(StateData *data) : vm(data->gfxSettings->resolution)
{
    this->data = data;

    states = data->states;

    gfxSettings = data->gfxSettings;

    window = data->window;

    acceptedKeys = data->acceptedKeys;

    currentPath = std::filesystem::current_path().string();

    quitState = false;
    isPaused = false;

    keytime = 0.f;
    keytimeMax = 15.f;

    mousetime = 0.f;
    mousetimeMax = 5.f;

    gridSize = data->gridSize;
}

State::~State()
{
}

/* DEFINED VIRTUAL FUNCTIONS */

void State::updateMousePositions(sf::View *view)
{
    mousePosScreen = sf::Mouse::getPosition();

    mousePosWindow = sf::Mouse::getPosition(*window);

    if (view)
        window->setView(*view);

    mousePosView = window->mapPixelToCoords(mousePosWindow);

    mousePosGrid = sf::Vector2i(
        static_cast<int>(mousePosView.x) / static_cast<int>(data->gridSize),
        static_cast<int>(mousePosView.y) / static_cast<int>(data->gridSize));

    window->setView(window->getDefaultView());
}

void State::updateKeytime(const float &dt)
{
    if (keytime < keytimeMax)
        keytime += 100.f * dt;
}

void State::updateMousetime(const float &dt)
{
    if (mousetime < mousetimeMax)
        mousetime += 100.f * dt;
}

void State::quit()
{
    quitState = true;
}

void State::pauseToggle()
{
    isPaused = !isPaused;
}

void State::pause()
{
    isPaused = true;
}

void State::resume()
{
    isPaused = false;
}

/* ACCESSORS */

const bool &State::hasAskedToQuit() const
{
    return quitState;
}

const bool State::hasCompletedKeytimeCicle()
{
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }

    return false;
}

const bool State::hasCompletedMousetimeCicle(sf::Mouse::Button mouseBtn)
{
    if (mousetime >= mousetimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouseBtn))
            mousetime = 0.f;

        return true;
    }

    return false;
}
