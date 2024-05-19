/*
 * HitboxComponent.cpp
 *
 *  Created on: 22 de abr. de 2024
 *      Author: renan
 */
#include "stdafx.h"
#include "HitboxComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */

HitboxComponent::HitboxComponent(sf::Sprite &sprite,
																 float offset_x, float offset_y,
																 float width, float height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitbox.setPosition(
			this->sprite.getPosition().x + offset_x,
			this->sprite.getPosition().y + offset_y);

	this->hitbox.setSize(sf::Vector2f(width, height));

	this->hitbox.setFillColor(sf::Color::Transparent);

	this->hitbox.setOutlineThickness(-1.f);					// TEMP
	this->hitbox.setOutlineColor(sf::Color::Green); // TEMP

	this->nextPosition.width = width;
	this->nextPosition.height = height;
}

HitboxComponent::~HitboxComponent()
{
}

/* FUNCTIONS */

void HitboxComponent::update()
{
	this->hitbox.setPosition(
			this->sprite.getPosition().x + this->offsetX,
			this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target)
{
	target.draw(this->hitbox);
}

/* ACCESSORS */

const sf::Vector2f &HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::Vector2f &HitboxComponent::getSize() const
{
	return this->hitbox.getSize();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect HitboxComponent::getNextPositionBounds(const sf::Vector2f &velocity, const float &dt)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x * dt;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y * dt;

	return nextPosition;
}

const bool HitboxComponent::intersects(sf::FloatRect &frect) const
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

/* MODIFIERS */

void HitboxComponent::setPosition(const sf::Vector2f &position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}
