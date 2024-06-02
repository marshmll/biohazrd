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

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
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
		ErrorHandler::throwErr("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n");

	ifs.close();
}

void MainMenuState::initGUI()
{
	// Background
	this->background.setSize(sf::Vector2f(static_cast<float>(this->vm.width), static_cast<float>(this->vm.height)));

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
		ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n");

	this->background.setTexture(&this->backgroundTexture);

	// Buttons
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(this->vm, 8.6f), gui::p2pY(this->vm, 40.f),
		gui::p2pX(this->vm, 19.5f), gui::p2pY(this->vm, 6.2f),
		&this->font, "New Game", gui::calc_char_size(this->vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(this->vm, 8.6f), gui::p2pY(this->vm, 49.f),
		gui::p2pX(this->vm, 19.5f), gui::p2pY(this->vm, 6.2f),
		&this->font, "Editor", gui::calc_char_size(this->vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(this->vm, 8.6f), gui::p2pY(this->vm, 58.f),
		gui::p2pX(this->vm, 19.5f), gui::p2pY(this->vm, 6.2f),
		&this->font, "Settings", gui::calc_char_size(this->vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(this->vm, 8.6f), gui::p2pY(this->vm, 82.f),
		gui::p2pX(this->vm, 19.5f), gui::p2pY(this->vm, 6.2f),
		&this->font, "Exit", gui::calc_char_size(this->vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

/* CONSTRUCTOR AND DESTRUCTOR */
MainMenuState::MainMenuState(StateData *data) : State(data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGUI();
	this->resetGUI();
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
	this->updateGUI();
}

void MainMenuState::render(sf::RenderTarget &target)
{

	target.draw(this->background);
	this->renderGUI(target);

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

void MainMenuState::updateGUI()
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
			this->states->push(new SettingsState(this->data, this));

		// Exit
		else if (this->buttons["EXIT_STATE"]->isPressed())
			this->quit();
	}
}

void MainMenuState::renderGUI(sf::RenderTarget &target)
{
	for (auto &it : this->buttons)
		it.second->render(target);
}

/* MODIFIERS */

void MainMenuState::resetGUI()
{
	for (auto &it : this->buttons)
		delete it.second;

	this->buttons.clear();

	this->initGUI();
}