/*
 * Entity parent class. Establishes basic entity
 * behaviors and properties.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "../PCH/stdafx.h"
#include "Entity.h"

/* INITIALIZERS */
void Entity::initVariables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
}

/* CONSTRUCTOR AND DESTRUCTOR */
Entity::Entity()
{
	/**
	 * @constructor
	 *
	 * Creates a entity instance.
	 * -> Initializes variables
	 */

	this->initVariables();
}

Entity::~Entity()
{
	/**
	 * @destructor
	 *
	 * Destructs entity instance.
	 * -> Deletes all entity components
	 */

	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;

}
/* COMPONENT FUNCTIONS */
void Entity::setTexture(sf::Texture &texture)
{
	/**
	 * @return void
	 *
	 * Sets texture for the entity sprite.
	 * Scale sprites up.
	 */

	this->sprite.setTexture(texture);

	this->sprite.setScale(3.f, 3.f); //Temp
}

void Entity::createHitboxComponent(
		const float offset_x, const float offset_y,
		const float width, const float height)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float accerelation, const float deceleration)
{
	/**
	 * @return void
	 *
	 * Creates a movement functionality component for the
	 * entity.
	 */

	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, accerelation, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
	/**
	 * @return void
	 *
	 * Creates a animation functionality component for the
	 * entity.
	 */

	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

/* FUNCTIONS */
void Entity::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the entity's sprite into a target.
	 */

	target.draw(this->sprite);

	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
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
	 * Moves the movement component (whick moves the sprite) into some
	 * x and y directions.
	 * -> Checks if the entity can move fisrt.
	 */

	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

