/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "MainMenuState.h"

/* INITIALIZERS */
void MainMenuState::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes MainMenuState variables
	 */
}

void MainMenuState::initBackground()
{
	/**
	 * @return void
	 *
	 * Sets background size to screen size, loads
	 * background texture and set background texture
	 * to the background area.
	 */

	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile(this->currentPath + "/Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw("ERROR::MAINMENUSTATE::INITBACKGROUND::ERROR LOADING" + this->currentPath
				+ "/Assets/Images/Backgrounds/main_menu_bg.png");
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	/**
	 * @return void
	 *
	 * Load font files..
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

	this->buttons["GAME_STATE"] = new Button(75, 340, 250, 50,
			&this->font, "New Game",
			sf::Color(150, 150, 150, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new Button(75, 440, 250, 50,
			&this->font, "Settings",
			sf::Color(150, 150, 150, 200), sf::Color(200, 200, 200, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(75, 640, 250, 50,
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

	this->initVariables();

	this->initBackground();

	this->initFonts();

	this->initKeybinds();

	this->initButtons();
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

//////////////////////////// REMOVE LATER: DEBUGGING STUFF ///////////////////////////////
//	sf::Text mouseText;
//	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 20));
//	mouseText.setFont(this->font);
//	mouseText.setCharacterSize(12);
//
//	std::stringstream ss;
//	ss << this->mousePosView.x << "   " << this->mousePosView.y;
//	mouseText.setString(ss.str());
//
//	target->draw(mouseText);
///////////////////////////////////////////////////////////////////////////////////////////
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

	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	// Checks if quit button was pressed
	if (this->buttons["EXIT_STATE"]->isPressed())
		this->quit();

	// Checks if new game button was pressed
	else if (this->buttons["GAME_STATE"]->isPressed())
		this->states->push(new GameState(this->window, this->acceptedKeys, this->states));

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
