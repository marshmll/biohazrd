/*
 * Entity parent class. Establishes basic entity
 * behaviors and properties.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "Entity.h"

Entity::Entity()
{
	/**
	 * @constructor
	 *
	 * Creates a entity instance.
	 * -> Set hitbox size.
	 * -> Set movement speed.
	 */
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->movementSpeed = 100.f;
}

Entity::~Entity()
{
	/**
	 * @destructor
	 *
	 * Destructs entity instance.
	 */
}

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

	target->draw(this->shape);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
	/**
	 * @return void
	 *
	 * Moves the entity according to x and y directions.
	 */

	this->shape.move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
}

