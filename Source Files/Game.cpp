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
	 * @return void
	 *
	 * Initializes game variables
	 */

	this->currentPath = std::filesystem::current_path().string();

	this->window = nullptr;
	this->fullscreen = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	/**
	 * @return void
	 *
	 * Initializes the RenderWindow
	 * -> Reads the window.ini file
	 * -> Sets title
	 * -> Sets height and width
	 * -> Sets fullscreen mode
	 * -> Sets framerate limit
	 * -> Sets vertical sync toggle
	 * -> Sets antialising level
	 * -> Creates the window.
	 */

	// Default values
	std::string title = "Default";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned int framerate_limit = 60;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	std::ifstream window_ini(currentPath + "/Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	// If window.ini was successfully opened
	if (window_ini.is_open())
	{
		// Read from window.ini to variables
		std::getline(window_ini, title);
		window_ini >> window_bounds.width;
		window_ini >> window_bounds.height;
		window_ini >> fullscreen;
		window_ini >> framerate_limit;
		window_ini >> vertical_sync_enabled;
		window_ini >> antialiasing_level;
	}
	// Close file
	window_ini.close();

	// Context
	this->windowSettings.antialiasingLevel = antialiasing_level;
	this->fullscreen = fullscreen;

	// Create the window

	if (this->fullscreen)
	{
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(window_bounds, title,
				sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
	}

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	/**
	 * @return void
	 *
	 * Initializes all accepted keys and adds them to a map.
	 * Maps strings to Key enum.
	 */

	std::ifstream ifs(this->currentPath + "/Config/accepted_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->acceptedKeys[key] = sf::Keyboard::Key(key_value);
		}
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
		this->states.top()->render(this->window);
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

	std::cout << "> [Game.cpp] Ending application..." << "\n";
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
