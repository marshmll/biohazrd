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
    this->attributeComponent = nullptr;
    this->skillComponent = nullptr;
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
    delete this->skillComponent;
}
/* COMPONENT FUNCTIONS */

void Entity::setTexture(sf::Texture &texture)
{
    this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(const float offset_x, const float offset_y,
                                   const float width, const float height)
{
    this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float max_velocity,
                                     const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, max_velocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
    this->attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{
    this->skillComponent = new SkillComponent();
}

/* FUNCTIONS */

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dir_x, dir_y, dt);
    }

    if (this->skillComponent)
    {
        this->skillComponent->gainExp(SKILLS::ENDURANCE, 1);
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

const sf::Vector2i Entity::getGridPosition(const int grid_size_i) const
{
    if (this->hitboxComponent)
        return sf::Vector2i(
            (int)this->hitboxComponent->getCenteredPosition().x / grid_size_i,
            (int)this->hitboxComponent->getCenteredPosition().y / grid_size_i);

    return sf::Vector2i(
        (int)this->sprite.getPosition().x / grid_size_i,
        (int)this->sprite.getPosition().y / grid_size_i);
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

const sf::Vector2f &Entity::getVelocity()
{
    return this->movementComponent->getVelocity();
}

const float &Entity::getMaxVelocity()
{
    return this->movementComponent->getMaxVelocity();
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
