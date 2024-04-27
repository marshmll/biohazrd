/*
 * Button.cpp
 *
 *  Created on: 14 de abr. de 2024
 *      Author: renan
 */

#include "Button.h"

/* CONSTRUCTOR AND DESTRUCTOR */
Button::Button(float x, float y, float width, float height,
		sf::Font *font, std::string text, unsigned char_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	/**
	 * @constructor
	 *
	 * Creates a button instance.
	 */

	this->btn_state = BTN_IDLE;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->text.setFont(*font);
	this->text.setString(text);
	this->text.setCharacterSize(char_size);
	this->text.setFillColor(text_idle_color);

	this->text.setPosition(
			this->shape.getPosition().x
					+ (this->shape.getGlobalBounds().width / 2.f)
					- this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y
					+ (this->shape.getGlobalBounds().height / 2.f)
					- this->text.getGlobalBounds().height / 2.f);
}

Button::~Button()
{

}

/* FUNCTIONS */
void Button::update(sf::Vector2f mousePos)
{
	/**
	 * @return void
	 *
	 * Updates buttons states and colors.
	 * -> Sets state to idle
	 * -> Check for new state
	 * -> Set new text and shape fill colors
	 */

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

	// Set text and fill color based on the state
	switch (this->btn_state)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;
	}
}
void Button::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the button into a target.
	 * -> Draws the shape into the target
	 * -> Draws the text into the center of the shape
	 */

	target.draw(this->shape);
	target.draw(this->text);
}

/* ACCESSORS */
const bool Button::isPressed() const
{
	/**
	 * @return const bool
	 *
	 * Returns if the button is pressed.
	 * An active status implies in a pressed button.
	 */

	return this->btn_state == BTN_ACTIVE;
}

