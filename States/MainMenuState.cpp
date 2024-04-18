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

	std::ifstream ifs(this->currentPath + "/Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
		{
			this->keybinds[action] = this->acceptedKeys->at(key);
		}
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes all the buttons of the MainMenuState.
	 */

	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50,
			&this->font, "New Game",
			sf::Color(150, 150, 150, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50,
			&this->font, "Quit",
			sf::Color(100, 100, 100, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 200));
}

/* CONSTRUCTOR AND DESTRUCTOR */
MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
		std::stack<State*> *states) :
		State(window, acceptedKeys, states)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor for State.
	 * Initializes fonts, keybinds and buttons.
	 */

	this->initFonts();

	this->initKeybinds();

	this->initButtons();

	this->background.setSize(static_cast<sf::Vector2f>(window->getSize()));

	this->background.setFillColor(sf::Color::Blue);
}

MainMenuState::~MainMenuState()
{
	/**
	 * @destructor
	 *
	 * Frees all the memory allocated for the buttons.
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* FUNCTIONS */
void MainMenuState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the MainMenuState.
	 * -> Checks for updates in the user input.
	 * -> Update buttons states.
	 */

	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Renders the main menu.
	 * -> Draw background
	 * -> Render buttons.
	 */

	target->draw(this->background);
	this->renderButtons(target);
}

void MainMenuState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the user input.
	 * -> Checks for quit the state.
	 * -> Updates mouse positions.
	 */

	this->checkForQuitState();

	this->updateMousePositions();
}

void MainMenuState::updateButtons()
{
	/**
	 * @return void
	 *
	 * Iterates over all buttons and update their states based on
	 * mouse click and position.
	 * Checks for exiting and pushing a new gamestate.
	 */

	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->quitState();
	}
	else if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->acceptedKeys, this->states));
	}
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Iterates over all buttons and renders them into a target.
	 */

	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::endState()
{
	/**
	 * @return void
	 *
	 * Function executed when the state is being ended.
	 */

	std::cout << "> [MainMenuState.cpp] Ending MainMenuState..." << "\n";
}
