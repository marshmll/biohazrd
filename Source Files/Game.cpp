/*
 * Game class that acts as the game engine.
 *
 *  Created on: 13 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "Game.h"

/* STATIC FUNCTIONS */

/* INITIALIZERS FUNCTIONS */
void Game::initVariables()
{
	/**
	 * Initializes game variables
	 */

	this->window = nullptr;
}

void Game::initWindow()
{
	/**
	 * @return void
	 *
	 * Initializes the RenderWindow
	 * -> Sets VideoMode height and width
	 * -> Creates a RenderWindow
	 */

	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "RPG Game", sf::Style::Titlebar | sf::Style::Close);
}

/* CONSTRUCTOR AND DESTRUCTOR */
Game::Game()
{
	/**
	 * Game Class Constructor
	 */

	this->initVariables();
	this->initWindow();
}

Game::~Game()
{
	/**
	 * Game Class Desstructor
	 */

	delete this->window;
}

/* MAIN FUNCTIONS */
void Game::run()
{
	/**
	 * @return void
	 *
	 * Keeps updating and rendering the game while
	 * the game is running
	 */

	while (this->isRunning())
	{
		this->updateDeltaTime();
		this->update();
		this->render();
	}

}
void Game::update()
{
	/**
	 * @return void
	 *
	 * Update game state
	 */

	this->pollSFMLEvents();
}

void Game::render()
{
	/**
	 * @return void
	 *
	 * Renders a frame into the window.
	 */

	this->window->clear();

	this->window->display();
}

/* AUXILIARY FUNCTIONS */
void Game::updateDeltaTime()
{
	/**
	 * @return void
	 *
	 * Updates the delta time which is taken to update and
	 * render a frame.
	 */


	this->dt = this->dtClock.restart().asSeconds();
	// std::cout << this->dt << std::endl;
}

void Game::pollSFMLEvents()
{
	/**
	 * @return void
	 *
	 * Poll events from the window
	 */

	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		default:
			break;
		}
	}
}

/* ACESSORS */
const bool Game::isRunning() const
{
	/**
	 * @return bool
	 *
	 * Returns if the game is currently running
	 */

	return this->window->isOpen();
}
