/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "MainMenuState.h"

/* INITIALIZERS */
void MainMenuState::initFonts()
{
	/**
	 * @return void
	 *
	 * Load font files.
	 * Throws an error if fails.
	 */

	if (!this->font.loadFromFile(this->currentPath + "/Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::INITFONTS::ERROR LOADING" + this->currentPath + "/Fonts/Dosis-Light.ttf\n");
	}
}

void MainMenuState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own binding to a key.
	 */

//	std::ifstream gamestate_keybinds_ini(this->currentPath + "/Config/gamestate_keybinds.ini");
//
//	if (gamestate_keybinds_ini.is_open())
//	{
//		std::string action = "";
//		std::string key = "";
//
//		while (gamestate_keybinds_ini >> action >> key)
//		{
//			this->keybinds[action] = this->acceptedKeys->at(key);
//		}
//	}
//
//	gamestate_keybinds_ini.close();
}

/* CONSTRUCTOR AND DESTRUCTOR */
MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys) :
		State(window, acceptedKeys)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor State(window, acceptedKeys) and
	 * initialize the keybinds for the state.
	 * -> Initializes fonts for MainMenuState.
	 */

	this->initFonts();

	this->initKeybinds();

	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));

	this->background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState()
{

}

/* FUNCTIONS */
void MainMenuState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the MainMenuState.
	 * -> Checks for updates in the user input.
	 */

	this->updateInput(dt);

}

void MainMenuState::render(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Renders MainMenuState into a target.
	 */

	target->draw(this->background);
}

void MainMenuState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the user input.
	 * -> Checks if the running state wants to quit.
	 * -> Updates mouse positions.
	 * -> Checks for keybinds and executes its respective
	 *    action.
	 */

	this->checkForQuitState();

	this->updateMousePositions();
}

void MainMenuState::endState()
{
	/**
	 * @return void
	 *
	 * Function executed when the state is being ended.
	 */

	std::cout << "> [GameState.cpp] Ending MainMenuState..." << "\n";
}
