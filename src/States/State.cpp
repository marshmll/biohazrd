/*
 * State class that serves as base class for generic states of the game.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */
#include "stdafx.h"
#include "State.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

State::State(StateData *data) : vm(data->gfxSettings->resolution)
{
    this->data = data;

    states = data->states;

    gfxSettings = data->gfxSettings;

    window = data->window;

    acceptedKeys = data->acceptedKeys;

    currentPath = filesystem::current_path().string();

    quitState = false;
    isPaused = false;

    keyTimer.restart();
    keyTimerMax = Int32(200);

    mouseTimer.restart();
    mouseTimerMax = Int32(50);

    gridSize = data->gridSize;
}

State::~State()
{
}

/* DEFINED VIRTUAL FUNCTIONS ===================================================================================== */

void State::updateMousePositions(View *view)
{
    mousePosScreen = Mouse::getPosition();

    mousePosWindow = Mouse::getPosition(*window);

    if (view)
        window->setView(*view);

    mousePosView = window->mapPixelToCoords(mousePosWindow);

    mousePosGrid = Vector2i(
        static_cast<int>(mousePosView.x) / static_cast<int>(data->gridSize),
        static_cast<int>(mousePosView.y) / static_cast<int>(data->gridSize));

    window->setView(window->getDefaultView());
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

/* ACCESSORS ===================================================================================================== */

const bool &State::hasAskedToQuit() const
{
    return quitState;
}

const bool State::hasElapsedKeyTimeMax(const bool is_key_pressed)
{
    if (keyTimer.getElapsedTime().asMilliseconds() >= keyTimerMax)
    {
        if (!is_key_pressed)
            return false;

        keyTimer.restart();

        return true;
    }

    return false;
}

const bool State::hasElapsedMouseTimeMax(const bool is_mouse_pressed)
{
    if (mouseTimer.getElapsedTime().asMilliseconds() >= mouseTimerMax)
    {
        if (!is_mouse_pressed)
            return false;

        mouseTimer.restart();

        return true;
    }

    return false;
}
