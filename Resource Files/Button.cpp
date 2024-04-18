/*
 * Button.cpp
 *
 *  Created on: 14 de abr. de 2024
 *      Author: renan
 */

#include "Button.h"

Button::Button(float x, float y, float width, float height,
		sf::Font *font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->btn_state = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(16);
	this->text.setFillColor(sf::Color::White);

	this->text.setPosition(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f)
					- this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f)
					- this->text.getGlobalBounds().height / 2.f
							);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
	// TODO Auto-generated destructor stub
}

/* FUNCTIONS */
void Button::update(sf::Vector2f mousePos)
{
	this->btn_state = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->btn_state = BTN_HOVER;

		// Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->btn_state = BTN_ACTIVE;
		}
	}

	if (this->btn_state != BTN_IDLE)
	{
		switch (this->btn_state)
		{
		case BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			break;
		case BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			break;
		default:
			break;
		}
	}
	else
	{
		this->shape.setFillColor(this->idleColor);
	}
}

void Button::render(sf::RenderTarget *target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

/* ACCESSORS */
const bool Button::isPressed() const
{
	return this->btn_state == BTN_ACTIVE;
}

