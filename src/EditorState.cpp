/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "EditorState.h"

/* INITIALIZERS */
void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, (int)this->data->gridSize, (int)this->data->gridSize);

	this->collision = false;
	this->type = TileTypes::DEFAULT;

	this->cameraSpeed = 500.f;

	this->layer = 0;
}

void EditorState::initEditorCamera()
{
	this->editorCamera.setSize(
			sf::Vector2f(this->data->gfxSettings->resolution.width, this->data->gfxSettings->resolution.height));

	this->editorCamera.setCenter(this->data->gfxSettings->resolution.width / 2.f,
															 this->data->gfxSettings->resolution.height / 2.f);
}

void EditorState::initKeybinds()
{
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
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		throw std::runtime_error("ERROR::EDITORSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
}

void EditorState::initText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(12);
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new gui::PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("SAVE", 500.f, "Save");
	this->pauseMenu->addButton("LOAD", 400.f, "Load");
}

void EditorState::initButtons()
{
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->data->gridSize, 10, 10, "Assets/Images/Tiles/tilesheet.png");
}

void EditorState::initGUI()
{
	// Sidebar
	this->sidebar.setSize(sf::Vector2f(60.f, this->data->gfxSettings->resolution.height));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineThickness(1.f);
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

	// World selector
	this->selectorRect.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));

	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 200));

	this->selectorRect.setOutlineColor(sf::Color::Red);
	this->selectorRect.setOutlineThickness(1.f);

	this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	// Texture selector
	this->textureSelector = new gui::TextureSelector(
			this->sidebar.getSize().x / 2 - 25.f, 20.f, 480.f, 480.f,
			this->data->gridSize,
			this->tileMap->getTileTextureSheet());
}

/* CONSTRUCTOR AND DESTRUCTOR */
EditorState::EditorState(StateData *data) : State(data)
{
	this->initVariables();

	this->initEditorCamera();

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
	for (auto &it : this->buttons)
		delete it.second;

	delete this->pauseMenu;

	delete this->tileMap;

	delete this->textureSelector;
}

/* FUNCTIONS */
void EditorState::update(const float &dt)
{
	this->updateMousePositions(&this->editorCamera);
	this->updateInput(dt);
	this->updateKeytime(dt);
	this->updateMousetime(dt);

	if (!this->isPaused)
	{
		this->updateButtons();
		this->updateGUI(dt);
		this->updateEditorInput(dt);
	}
	else
	{
		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void EditorState::render(sf::RenderTarget &target)
{
	// Render tilemap in the editor camera
	target.setView(this->editorCamera);
	this->tileMap->render(target, this->mousePosGrid);

	// Render buttons in the window view
	target.setView(this->window->getDefaultView());
	this->renderButtons(target);

	if (!this->isPaused)
	{
		this->renderGUI(target);
	}
	else
	{
		// Render pause menu in the window view
		target.setView(this->window->getDefaultView());
		this->pauseMenu->render(target);
	}
}

void EditorState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds["PAUSE"]) && this->hasCompletedKeytimeCicle())
		this->pauseToggle();
}

void EditorState::updateEditorInput(const float &dt)
{
	// Move view
	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_UP"]))
		this->editorCamera.move(0.f, std::floor(-this->cameraSpeed * dt));

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_DOWN"]))
		this->editorCamera.move(0.f, std::floor(this->cameraSpeed * dt));

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_LEFT"]))
		this->editorCamera.move(std::floor(-this->cameraSpeed * dt), 0.f);

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_RIGHT"]))
		this->editorCamera.move(std::floor(this->cameraSpeed * dt), 0.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hasCompletedKeytimeCicle())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->isActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect,
															 this->collision, this->type);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->isActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}

	// Toggle collision
	if (sf::Keyboard::isKeyPressed(this->keybinds["TOGGLE_COLLISION"]) && this->hasCompletedKeytimeCicle())
	{
		this->collision = !this->collision;
	}
	// Type increase
	else if (sf::Keyboard::isKeyPressed(this->keybinds["INCREASE_TYPE"]) && this->hasCompletedKeytimeCicle())
	{
		++this->type;
	}
	// Type decrease
	else if (sf::Keyboard::isKeyPressed(this->keybinds["DECREASE_TYPE"]) && this->hasCompletedKeytimeCicle())
	{
		if (this->type > 0)
			--this->type;
	}
}

void EditorState::updateButtons()
{
	for (auto &it : this->buttons)
		it.second->update(sf::Vector2f(this->mousePosWindow));
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->quit();

	else if (this->pauseMenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("test.biomap");

	else if (this->pauseMenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("test.biomap");
}

void EditorState::updateGUI(const float &dt)
{
	this->textureSelector->update(dt, this->mousePosWindow);

	if (!this->textureSelector->isActive())
	{
		this->selectorRect.setPosition(
				this->mousePosGrid.x * this->data->gridSize,
				this->mousePosGrid.y * this->data->gridSize);

		this->selectorRect.setTextureRect(this->textureRect);
	}

	this->cursorText.setPosition(sf::Vector2f(this->mousePosView.x + 40.f, this->mousePosView.y));

	std::stringstream ss;
	ss << this->mousePosWindow.x << " " << this->mousePosWindow.y << "\n"
		 << this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
		 << this->textureRect.left << " " << this->textureRect.top << "\n"
		 << "collision: " << (this->collision ? "true" : "false") << "\n"
		 << "type: " << this->type << "\n"
		 << "stacked tiles: " << this->tileMap->getAmountOfStackedTiles(mousePosGrid.x, mousePosGrid.y, this->layer);
	this->cursorText.setString(ss.str());
}

void EditorState::renderButtons(sf::RenderTarget &target)
{
	for (auto &it : this->buttons)
		it.second->render(target);
}

void EditorState::renderGUI(sf::RenderTarget &target)
{
	if (!this->textureSelector->isActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
	{
		// Render selector rect in the editor camera
		target.setView(this->editorCamera);
		target.draw(this->selectorRect);
	}

	// Render texture selector and sidebar in the window view
	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	// Render cursor text in the editor camera
	target.setView(this->editorCamera);
	target.draw(this->cursorText);
}
