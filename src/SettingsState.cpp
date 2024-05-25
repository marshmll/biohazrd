/*
 * SettingsState.cpp
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "SettingsState.h"

/* INITIALIZERS */

void SettingsState::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window->getSize()));

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error(
			"ERROR::SETTINGSSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n" + this->currentPath);
	}

	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n" + this->currentPath);
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string action = "";
		std::string key = "";

		while (ifs >> action >> key)
			this->keybinds[action] = this->acceptedKeys->at(key);
	}
	else
		throw std::runtime_error("ERROR::SETTINGSSTATE::INITKEYBINDS_COULD_NOT_LOAD_KEYBINDS\n" + this->currentPath);

	ifs.close();
}

void SettingsState::initGUI()
{
	this->buttons["BACK"] = new gui::Button(this->background.getGlobalBounds().width - 200.f, 660.f, 150.f, 50.f,
											&this->font, "Back", 30,
											sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
											sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(this->background.getGlobalBounds().width - 400.f, 660.f, 150.f, 50.f,
											 &this->font, "Apply", 30,
											 sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
											 sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;

	for (auto &mode : this->videoModes)
		modes_str.push_back(std::to_string(mode.width) + "x" + std::to_string(mode.height));

	this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(320, 320, 200, 50, this->font, modes_str.data(),
															   modes_str.size());
}

void SettingsState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(80.f, 320.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

/* CONSTRUCTOR AND DESTRUCTOR */

SettingsState::SettingsState(StateData *data) : State(data)
{
	this->initVariables();

	this->initBackground();

	this->initFonts();

	this->initKeybinds();

	this->initGUI();

	this->initText();
}

SettingsState::~SettingsState()
{
	// Delete buttons
	for (auto &it : this->buttons)
		delete it.second;

	// Delete ddls
	for (auto &it : this->dropDownLists)
		delete it.second;
}

/* FUNCTIONS */

void SettingsState::update(const float &dt)
{
	this->updateInput(dt);
	this->updateGUI(dt);
}

void SettingsState::render(sf::RenderTarget &target)
{
	target.draw(this->background);
	this->renderGUI(target);
	target.draw(this->optionsText);

	//////////////////////////// REMOVE LATER: DEBUGGING STUFF ////////////////////////////////
	// sf::Text mouseText;
	// mouseText.setPosition(sf::Vector2f(this->mousePosView.x, this->mousePosView.y - 20));
	// mouseText.setFont(this->font);
	// mouseText.setCharacterSize(12);

	// std::stringstream ss;
	// ss << this->mousePosView.x << " " << this->mousePosView.y;
	// mouseText.setString(ss.str());

	// target.draw(mouseText);
	///////////////////////////////////////////////////////////////////////////////////////////
}

void SettingsState::updateInput(const float &dt)
{
	this->updateMousePositions();
}

void SettingsState::updateGUI(const float &dt)
{
	// Updates all buttons based on mouse position view.
	for (auto &it : this->buttons)
		it.second->update(sf::Vector2f(this->mousePosWindow));

	// Updates all ddls based on mouse position view and dt.
	for (auto &it : this->dropDownLists)
		it.second->update(this->mousePosWindow, dt);

	// Checks for returning
	if (this->buttons["BACK"]->isPressed())
		this->quit();

	// Apply settings
	else if (this->buttons["APPLY"]->isPressed())
	{
		this->gfxSettings->resolution = this->videoModes[this->dropDownLists["RESOLUTIONS"]->getSelectedElementId()];

		this->window->create(this->gfxSettings->resolution, "BIOHAZRD", sf::Style::Titlebar | sf::Style::Close);
	}
}

void SettingsState::renderGUI(sf::RenderTarget &target)
{
	// Render buttons
	for (auto &it : this->buttons)
		it.second->render(target);

	// Render ddls
	for (auto &it : this->dropDownLists)
		it.second->render(target);
}
