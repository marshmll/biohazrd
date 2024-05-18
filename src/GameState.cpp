/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GameState.h"

/* INITIALIZERS */

void GameState::initBufferedRender()
{
	this->renderBuffer.create(
			this->data->gfxSettings->resolution.width,
			this->data->gfxSettings->resolution.height);

	this->renderSprite.setTexture(this->renderBuffer.getTexture());

	this->renderSprite.setTextureRect(
			sf::IntRect(0, 0, this->data->gfxSettings->resolution.width, this->data->gfxSettings->resolution.height));
}

void GameState::initView()
{
	this->playerCamera.setSize(
			sf::Vector2f(this->data->gfxSettings->resolution.width, this->data->gfxSettings->resolution.height));
	this->playerCamera.setCenter(this->data->gfxSettings->resolution.width / 2.f,
															 this->data->gfxSettings->resolution.height / 2.f);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
			this->keybinds[action] = this->acceptedKeys->at(key);
	}
	else
		throw std::runtime_error("GAMESTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		throw std::runtime_error("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Player/char_a_p1_0bas_humn_v01.png"))
		throw std::runtime_error("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE\n" + this->currentPath);
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new gui::PauseMenu(*this->window, this->font);
}

void GameState::initPlayers()
{
	this->player = new Player(0.f, 0.f, this->textures["PLAYER_SPRITESHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->data->gridSize, 10, 10, "Assets/Images/Tiles/tilesheet.png");
	this->tileMap->loadFromFile("test.biomap");
}

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(StateData *data) : State(data)
{
	this->initBufferedRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->player;
	delete this->tileMap;
}

/* FUNCTIONS */
void GameState::update(const float &dt)
{

	this->updateMousePositions(&this->playerCamera);
	this->updateKeytime(dt);
	this->updateInput(dt);

	// Not-paused update
	if (!this->isPaused)
	{
		this->updatePlayerCamera(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt);
		this->updateTileMap(dt);
	}

	// Paused update
	else
	{
		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget &target)
{
	this->renderToBuffer();

	target.draw(this->renderSprite);
}

void GameState::renderToBuffer()
{
	// Clear render buffer
	this->renderBuffer.clear();

	this->renderBuffer.setView(this->playerCamera);
	this->tileMap->render(this->renderBuffer, this->player);
	this->player->render(this->renderBuffer);

	if (this->isPaused)
	{
		this->renderBuffer.setView(this->renderBuffer.getDefaultView());
		this->pauseMenu->render(this->renderBuffer);
	}

	// Display render buffer
	this->renderBuffer.display();

	this->renderSprite.setTexture(this->renderBuffer.getTexture());
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds["PAUSE"]) && this->hasCompletedKeytimeCicle())
		this->pauseToggle();
}

void GameState::updatePlayerInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_UP"]))
	{
		this->player->move(0.f, -1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_DOWN"]))
	{
		this->player->move(0.f, 1.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_LEFT"]))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_RIGHT"]))
	{
		this->player->move(1.f, 0.f, dt);
	}
}

void GameState::updateTileMap(const float &dt)
{
	this->tileMap->update(dt);
	this->tileMap->updateCollision(dt, this->player);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->quit();
}

void GameState::updatePlayerCamera(const float &dt)
{
	this->playerCamera.setCenter(
			std::floor(this->player->getCenteredPosition().x),
			std::floor(this->player->getCenteredPosition().y));
}
