/*
 * HitboxComponent.cpp
 *
 *  Created on: 22 de abr. de 2024
 *      Author: renan
 */
#include "../PCH/stdafx.h"
#include "HitboxComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */
HitboxComponent::HitboxComponent(sf::Sprite &sprite,
		float offset_x, float offset_y,
		float width, float height) :
		sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	/**
	 * @constructor
	 *
	 * Creates a hitbox component for a entity.
	 * -> Sets position
	 * -> Sets size
	 * -> Sets fill color to transparent
	 */

	this->hitbox.setPosition(
			this->sprite.getPosition().x + offset_x,
			this->sprite.getPosition().y + offset_y);

	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);

	this->hitbox.setOutlineThickness(1.f);			// TEMP
	this->hitbox.setOutlineColor(sf::Color::Green); // TEMP
}

HitboxComponent::~HitboxComponent()
{

}

/* FUNCTIONS */
void HitboxComponent::update()
{
	/**
	 * @return void
	 *
	 * Updates the hitbox positions based on the sprite position.
	 */

	this->hitbox.setPosition(
			this->sprite.getPosition().x + this->offsetX,
			this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the hitbox into a target.
	 */

	target.draw(this->hitbox);
}

/* ACCESSORS */
const sf::Vector2f& HitboxComponent::getPosition() const
{
	/**
	 * @return const sf::Vector2f&
	 *
	 * Returns the hitbox position
	 */

	return this->hitbox.getPosition();
}

const sf::Vector2f& HitboxComponent::getSize() const
{
	/**
	 * @return const sf::Vector2f&
	 *
	 * Returns the hitbox size
	 */

	return this->hitbox.getSize();
}

const bool HitboxComponent::intersects(sf::FloatRect &frect) const
{
	/**
	 * @return const bool
	 *
	 * Checks if the hitbox has intersected some other object
	 * (sf::FloatRect).
	 */

	return this->hitbox.getGlobalBounds().intersects(frect);
}

/* MODIFIERS */
void HitboxComponent::setPosition(const sf::Vector2f &position)
{
	/**
	 * @return void
	 *
	 * Sets the hitbox position, and sets the sprite position
	 * with the offsets.
	 */

	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}
