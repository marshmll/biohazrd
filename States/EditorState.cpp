/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */
#include "../PCH/stdafx.h"
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

void EditorState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own function binding to a key.
	 */

	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
			this->keybinds[action] = this->acceptedKeys->at(key);
	}
	else
		throw std::runtime_error("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);

	ifs.close();
}

void EditorState::initFonts()
{
	/**
	 * @return void
	 *
	 * Loads font from file.
	 */

	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		throw std::runtime_error("ERROR::EDITORSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
}

void EditorState::initBackground()
{

}

void EditorState::initPauseMenu()
{
	/**
	 * @return void
	 *
	 * Initializes pause menu.
	 */

	this->pauseMenu = new gui::PauseMenu(*this->window, this->font);
}

void EditorState::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes all the buttons of the EditorState.
	 */

}

void EditorState::initGUI()
{
	this->selectorRect.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));

	this->selectorRect.setFillColor(sf::Color::Transparent);

	this->selectorRect.setOutlineColor(sf::Color::Red);
	this->selectorRect.setOutlineThickness(1.f);
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->data->gridSize, 10, 10);
}

/* CONSTRUCTOR AND DESTRUCTOR */
EditorState::EditorState(StateData *data) :
		State(data)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor for State.
	 * -> Initializes variables
	 * -> Initializes fonts
	 * -> Initializes keybinds
	 * -> Initializes buttons
	 */

	this->initVariables();

	this->initFonts();

	this->initKeybinds();

	this->initPauseMenu();

	this->initButtons();

	this->initGUI();

	this->initTileMap();
}

EditorState::~EditorState()
{
	/**
	 * @destructor
	 *
	 * Frees all the memory allocated for the buttons.
	 */

	for (auto &it : this->buttons)
		delete it.second;

	delete this->pauseMenu;

	delete this->tileMap;
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

	this->updateMousePositions();
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateMousetime(dt);

	if (!this->isPaused)
	{
		this->updateButtons();
		this->updateGUI();
		this->updateEditorInput(dt);
	}
	else
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
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

	this->tileMap->render(target);

	this->renderButtons(target);

	this->renderGUI(target);

	if (this->isPaused)
		this->pauseMenu->render(target);

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
	 */

	if (sf::Keyboard::isKeyPressed(this->keybinds["CLOSE"]) && this->hasCompletedKeytimeCicle())
	{
		if (!this->isPaused)
			this->pause();
		else
			this->resume();
	}

}
void EditorState::updateEditorInput(const float &dt)
{
	// Add a Tile to tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hasCompletedKeytimeCicle())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
	{
		this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
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

	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->quit();
}

void EditorState::updateGUI()
{
	this->selectorRect.setPosition(
			this->mousePosGrid.x * this->data->gridSize,
			this->mousePosGrid.y * this->data->gridSize);
}

void EditorState::renderButtons(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Iterates over all buttons and renders them into a target.
	 */

	for (auto &it : this->buttons)
		it.second->render(target);

}

void EditorState::renderGUI(sf::RenderTarget &target)
{
	target.draw(this->selectorRect);
}

