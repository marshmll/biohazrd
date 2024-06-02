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
	this->renderBuffer.create(this->vm.width, this->vm.height);

	this->renderSprite.setTexture(this->renderBuffer.getTexture());

	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->vm.width, this->vm.height));
}

void GameState::initView()
{
	this->playerCamera.setSize(sf::Vector2f(this->vm.width, this->vm.height));

	this->playerCamera.setCenter(this->vm.width / 2.f, this->vm.height / 2.f);
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
		ErrorHandler::throwErr("GAMESTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n");

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		ErrorHandler::throwErr("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
}

void GameState::initText()
{
	this->debugText.setFont(this->font);
	this->debugText.setCharacterSize(gui::calc_char_size(this->vm, 150));
	this->debugText.setPosition(this->vm.width - gui::p2pX(this->vm, 10.f), gui::p2pY(this->vm, 5.f));
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Player/char_a_p1_0bas_humn_v01.png"))
		ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE\n");
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new gui::PauseMenu(this->vm, this->font);
	this->pauseMenu->addButton("QUIT", gui::p2pY(this->vm, 83.7f), "Exit");
}

void GameState::initPlayers()
{
	this->player = new Player(10.f, 10.f, this->textures["PLAYER_SPRITESHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->vm);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->data->gridSize, 100, 100, "Assets/Images/Tiles/tilesheet.png");
	this->tileMap->loadFromFile("test.biomap");
}

void GameState::initShaders()
{
	if (!this->coreShader.loadFromFile("Shaders/vertex_shader.vert", "Shaders/fragment_shader.frag"))
		ErrorHandler::throwErr("GAMESTATE::INITSHADERS::ERR_COULD_NOT_LOAD_SHADERS\n");
}

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(StateData *data) : State(data)
{
	this->initBufferedRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initText();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initPlayerGUI();
	this->initTileMap();
	this->initShaders();
}

GameState::~GameState()
{
	delete this->pauseMenu;
	delete this->player;
	delete this->playerGUI;
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
		/* DEBUG! */
		std::stringstream ss;
		ss << "dt: " << dt << "ms";
		debugText.setString(ss.str());
		/*********/

		this->updatePlayerCamera(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt, this->mousePosView);
		this->playerGUI->update(dt);
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

	/* DEBUG! */
	target.draw(this->debugText);
	/**********/
}

void GameState::renderToBuffer()
{
	// Clear render buffer
	this->renderBuffer.clear();

	this->renderBuffer.setView(this->playerCamera);

	this->tileMap->render(
		this->renderBuffer,
		this->player->getGridPosition((int)this->data->gridSize), false,
		&this->coreShader, this->player->getCenteredPosition());

	this->player->render(this->renderBuffer, false, &this->coreShader);

	this->tileMap->deferredRender(
		this->renderBuffer,
		&this->coreShader, this->player->getCenteredPosition());

	this->renderBuffer.setView(this->renderBuffer.getDefaultView());
	this->playerGUI->render(this->renderBuffer);

	if (this->isPaused)
	{
		// this->renderBuffer.setView(this->renderBuffer.getDefaultView());
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

void GameState::updatePlayerGUI(const float &dt)
{
	this->playerGUI->update(dt);
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
		std::floor(this->player->getCenteredPosition().x + ((this->mousePosWindow.x) - static_cast<float>(this->vm.width / 2)) / 20.f),
		std::floor(this->player->getCenteredPosition().y + ((this->mousePosWindow.y) - static_cast<float>(this->vm.height / 2)) / 20.f));

	if (this->playerCamera.getCenter().x - this->playerCamera.getSize().x / 2.f < 0.f)
		this->playerCamera.setCenter(0.f + this->playerCamera.getSize().x / 2.f, this->playerCamera.getCenter().y);

	else if (this->playerCamera.getCenter().x + this->playerCamera.getSize().x / 2.f > this->tileMap->getSize().x)
		this->playerCamera.setCenter(this->tileMap->getSize().x - this->playerCamera.getSize().x / 2.f, this->playerCamera.getCenter().y);

	if (this->playerCamera.getCenter().y - this->playerCamera.getSize().y / 2.f < 0.f)
		this->playerCamera.setCenter(this->playerCamera.getCenter().x, 0.f + this->playerCamera.getSize().y / 2.f);

	else if (this->playerCamera.getCenter().y + this->playerCamera.getSize().y / 2.f > this->tileMap->getSize().y)
		this->playerCamera.setCenter(this->playerCamera.getCenter().x, this->tileMap->getSize().y - this->playerCamera.getSize().y / 2.f);
}
