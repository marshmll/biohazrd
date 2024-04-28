/*
 * SettingsState.cpp
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
 */

#include "SettingsState.h"

/* INITIALIZERS */
void SettingsState::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes SettingsState variables
	 */
}

void SettingsState::initBackground()
{
	/**
	 * @return void
	 *
	 * Sets background size to screen size, loads
	 * background texture and sets background texture
	 * to the background area.
	 */

	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile(this->currentPath + "/Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG");
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	/**
	 * @return void
	 *
	 * Loads font from file.
	 */

	if (!this->font.loadFromFile(this->currentPath + "/Fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT");
	}
}

void SettingsState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own function binding to a key.
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
	else
	{
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITKEYBINDS_COULD_NOT_LOAD_KEYBINDS");
	}

	ifs.close();
}

void SettingsState::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes all the buttons of the SettingsState.
	 */

	this->buttons["EXIT_STATE"] = new gui::Button(110.f, 660.f, 250.f, 50.f,
			&this->font, "Exit", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string test[] =
			{ "1980x720", "1280x800", "1280x720", "800x600" };

	this->ddl = new gui::DropDownList(200, 200, 150, 50, this->font, test, 4);
}

/* CONSTRUCTOR AND DESTRUCTOR */
SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
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

SettingsState::~SettingsState()
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

	delete this->ddl;
}

/* FUNCTIONS */
void SettingsState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the Settings State.
	 * -> Checks for updates in the user input.
	 * -> Update buttons.
	 */

	this->updateInput(dt);
	this->updateButtons();

	this->ddl->update(this->mousePosView, dt);
}

void SettingsState::render(sf::RenderTarget &target)
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

	this->ddl->render(target);

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

void SettingsState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the mouse input.
	 * -> Updates mouse positions.
	 */

	this->updateMousePositions();
}

void SettingsState::updateButtons()
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

	// Exit
	if (this->buttons["EXIT_STATE"]->isPressed())
		this->quit();
}

void SettingsState::renderButtons(sf::RenderTarget &target)
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

