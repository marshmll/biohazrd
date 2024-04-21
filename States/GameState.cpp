/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "GameState.h"

/* INITIALIZERS */
void GameState::initKeybinds()
{
	/**
	 * @return void
	 *
	 * Binds the accepted keys to its respective functionality.
	 * It might differ from state to state, each state can have
	 * its own binding to a key.
	 */

	std::ifstream ifs(this->currentPath + "/Config/gamestate_keybinds.ini");

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
		throw "GAMESTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS";
	}

	ifs.close();
}

void GameState::initTextures()
{
	/**
	 * @return void
	 *
	 * Initializes textures used in the game.
	 */

	if (!this->textures["SCARLET_SPRITESHEET"].loadFromFile(
			this->currentPath + "/Assets/Images/Sprites/Player/scarlet_spritesheet.png"))
	{
		throw "ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE";
	}
}

void GameState::initPlayers()
{
	/**
	 * @return void
	 *
	 * Initializes player(s).
	 */

	this->player = new Player(0.f, 0.f, this->textures["SCARLET_SPRITESHEET"]);
}

/* CONSTRUCTOR AND DESTRUCTOR */
GameState::GameState(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys,
		std::stack<State*> *states) :
		State(window, acceptedKeys, states)
{
	/**
	 * @constructor
	 *
	 * Calls the parent constructor State(window, acceptedKeys)
	 * -> Initializes the keybinds for the state.
	 * -> Initializes textures
	 * -> Initializes player(s)
	 */

	this->initKeybinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	/**
	 * @destructor
	 *
	 * Frees player allocated memory
	 */

	delete this->player;
}

/* FUNCTIONS */
void GameState::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the GameState.
	 * -> Checks for updates in the user input.
	 * -> Updates player.
	 */

	this->updateInput(dt);

	this->player->update(dt);
}

void GameState::render(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Renders GameState into a target (window).
	 * -> Renders player.
	 */

	this->player->render(target);

}

void GameState::updateInput(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the user input.
	 * -> Updates mouse positions.
	 * -> Checks for keybinds and executes its respective
	 *    action.
	 */

	this->updateMousePositions();

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
	else if (sf::Keyboard::isKeyPressed(this->keybinds["CLOSE"]))
	{
		this->quit();
	}
}
