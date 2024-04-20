/*
 * Entity parent class. Establishes basic entity
 * behaviors and properties.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "Entity.h"

/* INITIALIZERS */
void Entity::initVariables()
{
	this->movementComponent = nullptr;
}

Entity::Entity()
{
	/**
	 * @constructor
	 *
	 * Creates a entity instance.
	 */

	this->initVariables();
}

Entity::~Entity()
{
	/**
	 * @destructor
	 *
	 * Destructs entity instance.
	 */

}
/* COMPONENT FUNCTIONS */
void Entity::setTexture(sf::Texture &texture)
{
	/**
	 * @return void
	 *
	 * Sets texture for the entity sprite.
	 * -> Sets texture pointer
	 * -> Sets sprite pointer
	 */

	this->sprite.setTexture(texture);

	this->sprite.setScale(3.f, 3.f); //Temp
}

void Entity::createMovementComponent(const float maxVelocity)
{
	/**
	 * @return void
	 *
	 * Creates a movement functionality component for the
	 * entity. Requires a sprite reference.
	 */
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity);
}

/* FUNCTIONS */
void Entity::update(const float &dt)
{

}

void Entity::render(sf::RenderTarget *target)
{
	/**
	 * @return void
	 *
	 * Renders the entity's sprite into a target.
	 */

	target->draw(this->sprite);
}

void Entity::setPosition(const float x, const float y)
{
	/**
	 * @return void
	 *
	 * Sets a position to the entity's sprite.
	 */

	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
	/**
	 * @return void
	 *
	 * Moves the movement component into x and y directions
	 */

	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

