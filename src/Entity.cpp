/*
 * Entity parent class. Establishes basic entity
 * behaviors and properties.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
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
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->attributeComponent;
}
/* COMPONENT FUNCTIONS */

void Entity::setTexture(sf::Texture &texture)
{
	this->sprite.setTexture(texture);

	this->sprite.setScale(3.f, 3.f); // Temp
}

void Entity::createHitboxComponent(
		const float offset_x, const float offset_y,
		const float width, const float height)
{
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float accerelation, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, accerelation, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent()
{
	this->attributeComponent = new AttributeComponent();
}

/* FUNCTIONS */

void Entity::update(const float &dt)
{
}

void Entity::render(sf::RenderTarget &target)
{
}

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);
	}
}

/* ACCESSORS */

const sf::Vector2f &Entity::getPosition()
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();

	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenteredPosition()
{
	if (this->hitboxComponent)

		return this->hitboxComponent->getCenteredPosition();

	return sf::Vector2f(
			this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2);
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
				(int)this->hitboxComponent->getCenteredPosition().x / gridSizeI,
				(int)this->hitboxComponent->getCenteredPosition().y / gridSizeI);

	return sf::Vector2i(
			(int)this->sprite.getPosition().x / gridSizeI,
			(int)this->sprite.getPosition().y / gridSizeI);
}

const sf::Vector2f Entity::getSize()
{
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

const sf::FloatRect Entity::getGlobalBounds()
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	else
		return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float &dt)
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPositionBounds(this->movementComponent->getVelocity(), dt);
	else
		return sf::FloatRect();
}

const std::string Entity::getDirection()
{
	if (this->movementComponent)
		return this->movementComponent->getDirection();
	else
		return "NONE";
}

const bool Entity::hasCollided(sf::FloatRect &frect)
{
	if (this->hitboxComponent)
		return this->hitboxComponent->intersects(frect);
	else
		return false;
}

/* MODIFIERS */

void Entity::setPosition(const sf::Vector2f &position)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(position);
	else
		this->sprite.setPosition(position);
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}
