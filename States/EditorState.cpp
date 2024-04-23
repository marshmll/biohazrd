/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "EditorState.h"

/* INITIALIZERS */
void EditorState::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes MainMenuState variables
	 */
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	/**
	 * @return void
	 *
	 * Loads font from file.
	 */

	if (!this->font.loadFromFile(this->currentPath + "/Fonts/Dosis-Light.ttf"))
	{
		throw std::runtime_error("ERROR::EDITORSTATE::INITFONTS::COULD_NOT_LOAD_FONT");
	}
}

void EditorState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own function binding to a key.
	 */

	std::ifstream ifs(this->currentPath + "/Config/editorstate_keybinds.ini");

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
		throw std::runtime_error("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS");
	}

	ifs.close();
}

void EditorState::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes all the buttons of the MainMenuState.
	 */

}

/* CONSTRUCTOR AND DESTRUCTOR */
EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
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

	this->initFonts();

	this->initKeybinds();

	this->initButtons();
}

EditorState::~EditorState()
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
void EditorState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the MainMenuState.
	 * -> Checks for updates in the user input.
	 * -> Update buttons.
	 */

	this->updateInput(dt);
	this->updateButtons();
}

void EditorState::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the main menu.
	 * -> Draw background
	 * -> Render buttons.
	 */

	this->renderButtons(target);
//////////////////////////// REMOVE LATER: DEBUGGING STUFF ////////////////////////////////
	sf::Text mouseText;
	mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 20));
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << "   " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target.draw(mouseText);
///////////////////////////////////////////////////////////////////////////////////////////
}

void EditorState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the user input.
	 * -> Updates mouse positions.
	 */

	this->updateMousePositions();

	if (sf::Keyboard::isKeyPressed(this->keybinds["CLOSE"]))
	{
		this->quit();
	}
}

void EditorState::updateButtons()
{
	/**
	 * @return void
	 *
	 * Iterates over all buttons and update their states based on
	 * mouse click and position.
	 */

	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

}

void EditorState::renderButtons(sf::RenderTarget &target)
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
