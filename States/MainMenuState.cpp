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
	 * background texture and sets background texture
	 * to the background area.
	 */

	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error(
				"ERROR::MAINMENUSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n" + this->currentPath);
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	/**
	 * @return void
	 *
	 * Loads font from file.
	 */

	if (!this->font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		throw std::runtime_error("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
	}
}

void MainMenuState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own function binding to a key.
	 */

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
		{
			this->keybinds[action] = this->acceptedKeys->at(key);
		}
	}
	else
	{
		throw std::runtime_error("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);
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

	this->buttons["GAME_STATE"] = new gui::Button(110.f, 340.f, 250.f, 50.f,
			&this->font, "New Game", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(110.f, 420.f, 250.f, 50.f,
			&this->font, "Editor", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(110.f, 500.f, 250.f, 50.f,
			&this->font, "Settings", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(110.f, 660.f, 250.f, 50.f,
			&this->font, "Exit", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
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
	 * -> Initializes variables
	 * -> Initializes background
	 * -> Initializes fonts
	 * -> Initializes keybinds
	 * -> Initializes buttons
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
	 * -> Update buttons.
	 */

	this->updateMousetime(dt);
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the main menu.
	 * -> Draw background
	 * -> Render buttons.
	 */

	target.draw(this->background);
	this->renderButtons(target);

//////////////////////////// REMOVE LATER: DEBUGGING STUFF ////////////////////////////////
//	sf::Text mouseText;
//	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 20));
//	mouseText.setFont(this->font);
//	mouseText.setCharacterSize(12);
//
//	std::stringstream ss;
//	ss << this->mousePosView.x << " " << this->mousePosView.y;
//	mouseText.setString(ss.str());
//
//	target.draw(mouseText);
///////////////////////////////////////////////////////////////////////////////////////////
}

void MainMenuState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the mouse input.
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
	 * Executes a functionality for each button.
	 */

	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->hasCompletedMousetimeCicle(sf::Mouse::Left))
	{
		// New game
		if (this->buttons["GAME_STATE"]->isPressed())
			this->states->push(new GameState(this->window, this->acceptedKeys, this->states));

		// Editor state
		else if (this->buttons["EDITOR_STATE"]->isPressed())
			this->states->push(new EditorState(this->window, this->acceptedKeys, this->states));

		// Settings
		else if (this->buttons["SETTINGS_STATE"]->isPressed())
			this->states->push(new SettingsState(this->window, this->acceptedKeys, this->states));

		// Exit
		else if (this->buttons["EXIT_STATE"]->isPressed())
			this->quit();
	}
}

void MainMenuState::renderButtons(sf::RenderTarget &target)
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
