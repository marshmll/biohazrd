/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "MainMenuState.h"

/* INITIALIZERS */

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error(
			"ERROR::MAINMENUSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n" + this->currentPath);
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
	{
		throw std::runtime_error("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
	}
}

void MainMenuState::initKeybinds()
{
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
		throw std::runtime_error("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);
	}

	ifs.close();
}

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new gui::Button(p2pX(8.6f), p2pY(40.f), 250.f, 50.f,
												  &this->font, "New Game", 30,
												  sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
												  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(p2pX(8.6f), p2pY(49.f), 250.f, 50.f,
													&this->font, "Editor", 30,
													sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
													sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(p2pX(8.6f), p2pY(58.f), 250.f, 50.f,
													  &this->font, "Settings", 30,
													  sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
													  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(p2pX(8.6f), p2pY(82.f), 250.f, 50.f,
												  &this->font, "Exit", 30,
												  sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
												  sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

/* CONSTRUCTOR AND DESTRUCTOR */
MainMenuState::MainMenuState(StateData *data) : State(data)
{
	this->initVariables();

	this->initBackground();

	this->initFonts();

	this->initKeybinds();

	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto &it : this->buttons)
		delete it.second;
}

/* FUNCTIONS */

void MainMenuState::update(const float &dt)
{
	this->updateMousetime(dt);
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget &target)
{

	target.draw(this->background);
	this->renderButtons(target);

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

void MainMenuState::updateInput(const float &dt)
{
	this->updateMousePositions();
}

void MainMenuState::updateButtons()
{
	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(this->mousePosView);

	if (this->hasCompletedMousetimeCicle(sf::Mouse::Left))
	{
		// New game
		if (this->buttons["GAME_STATE"]->isPressed())
			this->states->push(new GameState(this->data));

		// Editor state
		else if (this->buttons["EDITOR_STATE"]->isPressed())
			this->states->push(new EditorState(this->data));

		// Settings
		else if (this->buttons["SETTINGS_STATE"]->isPressed())
			this->states->push(new SettingsState(this->data));

		// Exit
		else if (this->buttons["EXIT_STATE"]->isPressed())
			this->quit();
	}
}

void MainMenuState::renderButtons(sf::RenderTarget &target)
{
	for (auto &it : this->buttons)
		it.second->render(target);
}
