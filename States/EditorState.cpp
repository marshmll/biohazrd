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

	this->textureRect = sf::IntRect(0, 0, (int) this->data->gridSize, (int) this->data->gridSize);
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

void EditorState::initText()
{
	/**
	 * @return void
	 *
	 * Initializes the texts for the state.
	 */

	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(12);
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

void EditorState::initTileMap()
{
	/**
	 * @return void
	 *
	 * Initializes the tilemap for the editor.
	 */

	this->tileMap = new TileMap(this->data->gridSize, 10, 10);
}

void EditorState::initGUI()
{
	/**
	 * @return void
	 *
	 * Initializes the GUI elements.
	 * -> initializes selector rect.
	 */

	this->selectorRect.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 200));

	this->selectorRect.setOutlineColor(sf::Color::Red);
	this->selectorRect.setOutlineThickness(1.f);

	this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 480.f, 480.f, this->data->gridSize,
			this->tileMap->getTileTextureSheet());
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

	this->initText();

	this->initKeybinds();

	this->initPauseMenu();

	this->initButtons();

	this->initTileMap();

	this->initGUI();
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

	delete this->textureSelector;
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

	if (!this->isPaused)
		this->renderGUI(target);
	else
		this->pauseMenu->render(target);
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
	/**
	 * @return void
	 *
	 * Updates the input specific for the editor
	 */

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hasCompletedKeytimeCicle())
	{
		if (!this->textureSelector->isActive())
			this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);

		else
		{
			this->textureRect = this->textureSelector->getTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
	{
		if (!this->textureSelector->isActive())
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
	/**
	 * @return void
	 *
	 * Updates pause menu buttons
	 */

	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->quit();
}

void EditorState::updateGUI()
{
	/**
	 * @return void
	 *
	 * Updates the GUI elements.
	 */

	this->textureSelector->update(this->mousePosWindow);

	if (!this->textureSelector->isActive())
	{
		this->selectorRect.setPosition(
				this->mousePosGrid.x * this->data->gridSize,
				this->mousePosGrid.y * this->data->gridSize);

		this->selectorRect.setTextureRect(this->textureRect);
	}

	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x + 100.f, this->mousePosView.y));

	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "\n"
			<< this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
			<< this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());

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
	/**
	 * @return void
	 *
	 * Renders the GUI elements into a target.
	 */

	if (!this->textureSelector->isActive())
		target.draw(this->selectorRect);

	this->textureSelector->render(target);

	target.draw(this->cursorText);
}

