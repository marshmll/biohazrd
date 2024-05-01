/*
 * Game class that acts as the game engine.
 *
 *  Created on: 13 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "../PCH/stdafx.h"
#include "Game.h"

/* STATIC FUNCTIONS */

/* INITIALIZERS FUNCTIONS */
void Game::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes game variables
	 */

	this->currentPath = std::filesystem::current_path().string();

	this->window = nullptr;

	this->dt = 0.f;
}

void Game::initGraphicsSettings()
{
	/**
	 * @return void
	 *
	 * Initializes graphics settings from a file.
	 */

	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	/**
	 * @return void
	 *
	 * Initializes the RenderWindow
	 * -> Creates the window.
	 */

	// Create the window
	if (this->gfxSettings.fullscreen) // If in fullscreen mode
	{
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,
				sf::Style::Fullscreen, this->gfxSettings.contextSettings);
	}
	else // If in window mode
	{
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,
				sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
	}

	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
	/**
	 * @return void
	 *
	 * Initializes all accepted keys and adds them to a map.
	 * Maps strings to Key enum.
	 */

	std::ifstream ifs("Config/accepted_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->acceptedKeys[key] = sf::Keyboard::Key(key_value);
		}
	}
	else
	{
		throw std::runtime_error("GAME::INITKEYS::ERROR_COULD_NOT_LOAD_ACCEPTED_KEYS_INI\n" + this->currentPath);
	}

	ifs.close();

//	for (auto i : this->acceptedKeys)
//	{
//		std::cout << i.first << " " << i.second << "\n";
//	}
}

void Game::initStates()
{
	/**
	 * @return void
	 *
	 * Initializates states and push them into states stack.
	 */

	this->states.push(new MainMenuState(this->window, &this->acceptedKeys, &this->states));
}

/* CONSTRUCTOR AND DESTRUCTOR */
Game::Game()
{
	/**
	 * @constructor
	 *
	 * Game Class Constructor
	 * -> Initializes variables
	 * -> Initializes window
	 * -> Initializes keys
	 * -> Initializes states.
	 */

	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	/**
	 * @destructor
	 *
	 * Frees the window allocated memory and free all
	 * states allocated memory.
	 */

	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
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
	 * Polls SFML events and updates the states
	 * in the game.
	 * -> Poll SFML events
	 * -> Update the top state in the stack
	 * -> Check for ending the top state in the stack
	 * -> If there are not more states in the stack,
	 *    exit the applicaiton.
	 */

	this->pollSFMLEvents();

	// If there are still states available
	if (!this->states.empty())
	{
		// Update the top state in the states stack
		this->states.top()->update(this->dt);

		// If the state wants to end
		if (this->states.top()->hasAskedToQuit())
		{
			// Delete the state and pop it from the stack.
			delete this->states.top();
			this->states.pop();
		}
	}
	// If there are no states
	else
	{
		// Quit application.
		this->endApplication();
	}
}

void Game::render()
{
	/**
	 * @return void
	 *
	 * Renders a frame into the window.
	 */

	// Clear window
	this->window->clear();

	// If there are states stack
	if (!this->states.empty())
	{
		// Render them into the window.
		this->states.top()->render(*this->window);
	}

	// Display window
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
			this->endApplication();
			break;

		default:
			break;
		}
	}
}

void Game::endApplication()
{
	/**
	 * @return void
	 *
	 * Closes the window and end application.
	 */

	this->window->close();
}

/* ACESSORS */
const bool Game::isRunning() const
{
	/**
	 * @return const bool
	 *
	 * Returns if the game is currently running
	 */

	return this->window->isOpen();
}
