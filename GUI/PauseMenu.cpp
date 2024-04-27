/*
 * PauseMenu.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "PauseMenu.h"

/* INITIALIZERS */
void PauseMenu::initButtons()
{
	/**
	 * @return void
	 *
	 * Initializes pause menu buttons.
	 */

	this->addButton("QUIT", 670.f, "Exit");
}

/* CONSTRUCTOR AND DESTRUCTOR */
PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font) :
		font(font)
{
	/**
	 * @constructor
	 *
	 * Creates the pause menu.
	 * -> Sets background
	 * -> Sets container
	 * -> Sets the text
	 * -> Initialize buttons.
	 */

	// Background
	this->background.setSize(sf::Vector2f(window.getSize()));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	// Container
	this->container.setSize(sf::Vector2f(window.getSize().x / 4.f, window.getSize().y - 60.f));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setPosition(sf::Vector2f(
			this->background.getSize().x / 2 - this->container.getSize().x / 2,
			this->background.getSize().y / 2 - this->container.getSize().y / 2));

	// Pause menu text
	this->pmenuText.setFont(this->font);
	this->pmenuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->pmenuText.setCharacterSize(40);
	this->pmenuText.setString("PAUSED");

	this->pmenuText.setPosition(sf::Vector2f(
			this->container.getPosition().x + this->container.getSize().x / 2
					- this->pmenuText.getGlobalBounds().width / 2,
			this->container.getPosition().y + 60.f
					- this->pmenuText.getGlobalBounds().height / 2));

	this->initButtons();
}

PauseMenu::~PauseMenu()
{
	/**
	 * @destructor
	 *
	 * Free allocated memory from the pause menu
	 * and destructs is.
	 */

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

/* FUNCIONS */
void PauseMenu::update(const sf::Vector2f &mousePos)
{
	/**
	 * @return void
	 *
	 * Updates the pause menu.
	 * -> Updates all buttons
	 */

	for (auto &it : this->buttons)
	{
		it.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the pause menu into a render target.
	 * -> Renders background
	 * -> Renders container
	 * -> Renders text
	 * -> Renders buttons
	 */

	target.draw(this->background);
	target.draw(this->container);
	target.draw(this->pmenuText);

	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void PauseMenu::addButton(std::string key, float y, const std::string text)
{
	/**
	 * @return void
	 *
	 * Adds a button to the pause menu
	 * Parameters: key, y and text.
	 */

	float width = 250.f;

	float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2;

	this->buttons[key] = new Button(x, y, width, 50.f,
			&this->font, text, 30,
			sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
			sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	/**
	 * @return const bool&
	 *
	 * Returns if a button is pressed based on its key.
	 */

	return this->buttons[key]->isPressed();
}

/* ACCESSORS */
std::map<std::string, Button*>& PauseMenu::getButtons()
{
	/**
	 * @return std::map<std::string, Button*>&
	 *
	 * Returns the buttons map reference.
	 */

	return this->buttons;
}
