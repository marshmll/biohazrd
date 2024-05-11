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

/* ACCESSORS */
const sf::Vector2f& Entity::getPosition()
{
	/**
	 * @return const sf::Vector2f&
	 *
	 * Returns the position of the hitbox or the position
	 * of the sprite, if there is no hitbox.
	 */

	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenteredPosition()
{
	/**
	 * @return const sf::Vector2f
	 *
	 * Returns the position of the center of the sprite.
	 */

	return sf::Vector2f(
			this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
}

const sf::Vector2f Entity::getSize()
{
	/**
	 * @return const sf::Vector2f
	 *
	 * Returns the hitbox size, or the sprite size
	 * if there is not hitbox.
	 */

	if (this->hitboxComponent)
	{
		return sf::Vector2f(
				this->hitboxComponent->getSize().x,
				this->hitboxComponent->getSize().y);
	}
	else
	{
		return sf::Vector2f(
				this->sprite.getGlobalBounds().width,
				this->sprite.getGlobalBounds().height);
	}

}

const bool Entity::hasCollided(sf::FloatRect &frect)
{
	/**
	 * @return const bool
	 *
	 * Returns if the entity's hitbox has intersected a FloatRect.
	 * -> Returns false if the entity does not have a hitbox component.
	 */

	if (this->hitboxComponent)
		return this->hitboxComponent->intersects(frect);
	else
		return false;
}

/* MODIFIERS */
void Entity::setPosition(const sf::Vector2f &position)
{
	/**
	 * @return void
	 *
	 * Sets a position to the entity's hitbox, or to
	 * the entity's sprite, if there's no hitbox.
	 */

	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(position);
	else
		this->sprite.setPosition(position);
}

