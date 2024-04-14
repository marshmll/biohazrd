/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "GameState.h"

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(sf::RenderWindow *window) :
		State(window)
{

}

GameState::~GameState()
{

}


/* FUNCTIONS */
void GameState::update(const float &dt)
{
	this->updateKeybinds(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "A" << "\n";
	}

}

void GameState::render(sf::RenderTarget *target)
{

}

void GameState::updateKeybinds(const float &dt)
{
	this->checkForQuit();

}

void GameState::endState()
{
	std::cout << "> [GameState.cpp] Ending GameState..." << "\n";
}
