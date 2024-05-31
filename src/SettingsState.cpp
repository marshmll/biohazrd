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
	const sf::VideoMode &vm = this->data->gfxSettings->resolution;

	// Background
	this->background.setSize(sf::Vector2f(vm.width, vm.height));

	if (!this->backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
	{
		throw std::runtime_error(
			"ERROR::SETTINGSSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n" + this->currentPath);
	}

	this->background.setTexture(&this->backgroundTexture);

	// Buttons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(vm, 84.3f), gui::p2pY(vm, 82.5f),
		gui::p2pX(vm, 11.7f), gui::p2pY(vm, 6.2f),
		&this->font, "Back", gui::calc_char_size(vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(vm, 68.7f), gui::p2pY(vm, 82.5f),
		gui::p2pX(vm, 11.7f), gui::p2pY(vm, 6.2f),
		&this->font, "Apply", gui::calc_char_size(vm, 65),
		sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	// Drop down lists
	std::vector<std::string> modes_str;

	// Get the video modes strings
	for (auto &mode : this->videoModes)
		modes_str.push_back(std::to_string(mode.width) + "x" + std::to_string(mode.height));

	// Find the index of the current videomode in videomodes
	unsigned i;
	auto it = std::find(this->videoModes.begin(), this->videoModes.end(), this->vm);
	if (it != this->videoModes.end())
	{
		auto index = std::distance(this->videoModes.begin(), it);

		i = static_cast<unsigned>(index);
	}

	// Create the drop down list.
	this->dropDownLists["RESOLUTIONS"] = new gui::DropDownList(
		gui::p2pX(vm, 25.f), gui::p2pY(vm, 40.f),
		gui::p2pX(vm, 15.6f), gui::p2pY(vm, 6.2f),
		this->font, modes_str.data(), modes_str.size(),
		gui::calc_char_size(vm, 120), i);

	// Create options text
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(gui::p2pX(vm, 6.2f), gui::p2pY(vm, 40.f));
	this->optionsText.setCharacterSize(gui::calc_char_size(vm, 70));
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));
	this->optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

void SettingsState::resetGUI()
{
	for (auto &it : this->buttons)
		delete it.second;
	this->buttons.clear();

	for (auto &it : this->dropDownLists)
		delete it.second;
	this->dropDownLists.clear();

	this->initGUI();
}

/* CONSTRUCTOR AND DESTRUCTOR */

SettingsState::SettingsState(StateData *data, MainMenuState *main_menu_state) : State(data)
{
	this->mainMenuState = main_menu_state;

	this->initVariables();

	this->initFonts();

	this->initKeybinds();

	this->initGUI();
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

		this->window->create(this->gfxSettings->resolution, "BIOHAZRD", sf::Style::Fullscreen);

		this->resetGUI();

		this->mainMenuState->resetGUI();
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
