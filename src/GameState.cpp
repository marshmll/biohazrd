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
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own binding to a key.
	 */

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
	/**
	 * @return void
	 *
	 * Loads font from file.
	 */

	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		throw std::runtime_error("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
}

void GameState::initTextures()
{
	/**
	 * @return void
	 *
	 * Initializes textures used in the game.
	 */

	if (!this->textures["PLAYER_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Player/char_a_p1_0bas_humn_v01.png"))
		throw std::runtime_error("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE\n" + this->currentPath);
}

void GameState::initPauseMenu()
{
	/**
	 * @return void
	 *
	 * Initializes pause menu.
	 */

	this->pauseMenu = new gui::PauseMenu(*this->window, this->font);
}

void GameState::initPlayers()
{
	/**
	 * @return void
	 *
	 * Initializes player(s).
	 */

	this->player = new Player(0.f, 0.f, this->textures["PLAYER_SPRITESHEET"]);
}

void GameState::initTileMap()
{
	/**
	 * @return void
	 *
	 * Initializes a tilemap for the gamestate.
	 */

	this->tileMap = new TileMap(this->data->gridSize, 10, 10, "Assets/Images/Tiles/tilesheet.png");
	this->tileMap->loadFromFile("test.biomap");
}

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(StateData *data) :
		State(data)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor State(window, acceptedKeys)
	 * -> Initializes the keybinds for the state.
	 * -> Initializes fonts
	 * -> Initializes textures
	 * -> Initializes pause menu
	 * -> Initializes player(s)
	 */

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
	/**
	 * @destructor
	 *
	 * Frees player allocated memory
	 */

	delete this->pauseMenu;
	delete this->player;
	delete this->tileMap;
}

/* FUNCTIONS */
void GameState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the GameState.
	 * -> Checks for updates in the state input.
	 * -> Checks for updates in the player input, if NOT paused.
	 * -> Checks for updates in the player input, if NOT paused.
	 * -> Updates player, if NOT paused.
	 * -> Updates pause menu if PAUSED.
	 * -> Uptades pause menu buttons if PAUSED.
	 */

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
	/**
	 * @return void
	 *
	 * Renders GameState into a render texture buffer.
	 * -> Display the buffered texture into the target.
	 */
	this->renderToBuffer();

	target.draw(this->renderSprite);

}

void GameState::renderToBuffer()
{
	/**
	 * @return void
	 *
	 * Renders everything into a RenderTexture buffer.
	 * -> Clear the buffer.
	 * -> Render into the buffer
	 * -> Display the buffer
	 * -> Set renderSprite texture to buffer.
	 */

	// Clear render buffer
	this->renderBuffer.clear();

	this->renderBuffer.setView(this->playerCamera);
	this->tileMap->render(this->renderBuffer);
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
	/**
	 * @return void
	 *
	 * Updates inputs related to the state.
	 */

	if (sf::Keyboard::isKeyPressed(this->keybinds["PAUSE"]) && this->hasCompletedKeytimeCicle())
		this->pauseToggle();
}

void GameState::updatePlayerInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player input.
	 *
	 * Checks for keybinds and executes its respective
	 * action.
	 */

	if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_UP"]))
		this->player->move(0.f, -1.f, dt);

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_DOWN"]))
		this->player->move(0.f, 1.f, dt);

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_LEFT"]))
		this->player->move(-1.f, 0.f, dt);

	else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_RIGHT"]))
		this->player->move(1.f, 0.f, dt);
}

void GameState::updateTileMap(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates tilemap and collisions.
	 */

	this->tileMap->update();
	this->tileMap->updateCollision(this->player);
}

void GameState::updatePauseMenuButtons()
{
	/**
	 * @return void
	 *
	 * Updates button interactions from the pause menu.
	 * Executes its functionality.
	 */

	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->quit();
}

void GameState::updatePlayerCamera(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player camera, keeps player on
	 * the center of the screen.
	 */

	this->playerCamera.setCenter(
			std::floor(this->player->getCenteredPosition().x),
			std::floor(this->player->getCenteredPosition().y));
}
