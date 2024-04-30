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

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error(
				"ERROR::SETTINGSSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n" + this->currentPath);
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

	if (!this->font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
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
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITKEYBINDS_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);
	}

	ifs.close();
}

void SettingsState::initGUI()
{
	/**
	 * @return void
	 *
	 * Initializes all GUI elements.
	 */

	this->buttons["BACK"] = new gui::Button(this->background.getGlobalBounds().width - 200.f, 660.f, 150.f, 50.f,
			&this->font, "Back", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(this->background.getGlobalBounds().width - 400.f, 660.f, 150.f, 50.f,
			&this->font, "Apply", 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::string li[] =
			{ "1980x1080", "1280X800", "1280X720", "800x600", "640x480" };

	this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(100, 400, 200, 50, this->font, li, 5);
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

	this->initGUI();
}

SettingsState::~SettingsState()
{
	/**
	 * @destructor
	 *
	 * Frees all the memory allocated for the buttons.
	 */

	// Delete buttons
	for (auto &it : this->buttons)
		delete it.second;

	// Delete ddls
	for (auto &it : this->dropDownLists)
		delete it.second;
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
	this->updateGUI(dt);
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
	this->renderGUI(target);

//////////////////////////// REMOVE LATER: DEBUGGING STUFF ////////////////////////////////
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 20));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target.draw(mouseText);
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

void SettingsState::updateGUI(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates all GUI elements.
	 */

	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	// Updates all ddls based on mouse position view and dt.
	for (auto &it : this->dropDownLists)
		it.second->update(this->mousePosView, dt);

	// Checks for returning
	if (this->buttons["BACK"]->isPressed())
		this->quit();

	// Apply settings
	else if (this->buttons["APPLY"]->isPressed())
		this->quit();
}

void SettingsState::renderGUI(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders all GUI elements.
	 */

	// Render buttons
	for (auto &it : this->buttons)
		it.second->render(target);

	// Render ddls
	for (auto &it : this->dropDownLists)
		it.second->render(target);
}

