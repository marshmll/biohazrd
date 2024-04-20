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
	this->sprite = nullptr;
	this->texture = nullptr;
	this->movementSpeed = 100.f;
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

	delete this->sprite;

}
/* COMPONENT FUNCTIONS */
void Entity::createSprite(sf::Texture *texture)
{
	/**
	 * @return void
	 *
	 * Creates the entity sprite.
	 * -> Sets texture pointer
	 * -> Sets sprite pointer
	 */

	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);

	this->sprite->setScale(4.f, 4.f); //Temp
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
	 * Renders the entity into a target.
	 */

	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}

void Entity::setPosition(const float x, const float y)
{
	/**
	 * @return void
	 *
	 * Sets a position to the entity class if available.
	 */

	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
	/**
	 * @return void
	 *
	 * Moves the entity according to x and y directions, if avaivable..
	 */

	if (this->sprite)
	{
		this->sprite->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
	}
}

