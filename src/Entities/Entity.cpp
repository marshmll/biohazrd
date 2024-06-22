/*
 * Entity parent class. Establishes basic entity
 * behaviors and properties.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "Entity.h"

/* INITIALIZERS ================================================================================================== */

void Entity::initVariables()
{
    hitboxComponent = nullptr;
    movementComponent = nullptr;
    animationComponent = nullptr;
    attributeComponent = nullptr;
    skillComponent = nullptr;
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

Entity::Entity()
{
    initVariables();
}

Entity::~Entity()
{
    delete hitboxComponent;
    delete movementComponent;
    delete animationComponent;
    delete attributeComponent;
    delete skillComponent;
}
/* COMPONENT FUNCTIONS ========================================================================================== */

void Entity::setTexture(sf::Texture &texture)
{
    sprite.setTexture(texture);
}

void Entity::createHitboxComponent(const float offset_x, const float offset_y,
                                   const float width, const float height)
{
    hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float max_velocity,
                                     const float acceleration, const float deceleration)
{
    movementComponent = new MovementComponent(sprite, max_velocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet)
{
    animationComponent = new AnimationComponent(sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
    attributeComponent = new AttributeComponent(level);
}

void Entity::createSkillComponent()
{
    skillComponent = new SkillComponent();
}

/* FUNCTIONS ===================================================================================================== */

void Entity::move(const float dir_x, const float dir_y, const float &dt)
{
    if (movementComponent)
    {
        movementComponent->move(dir_x, dir_y, dt);
    }

    if (skillComponent)
    {
        skillComponent->gainExp(SKILLS::ENDURANCE, 1);
    }
}

/* ACCESSORS ===================================================================================================== */

const sf::Vector2f &Entity::getPosition()
{
    if (hitboxComponent)
        return hitboxComponent->getPosition();

    return sprite.getPosition();
}

const sf::Vector2f Entity::getCenteredPosition()
{
    if (hitboxComponent)

        return hitboxComponent->getCenteredPosition();

    return sf::Vector2f(
        sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
        sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
}

const sf::Vector2i Entity::getGridPosition(const int grid_size_i) const
{
    if (hitboxComponent)
        return sf::Vector2i(
            (int)hitboxComponent->getCenteredPosition().x / grid_size_i,
            (int)hitboxComponent->getCenteredPosition().y / grid_size_i);

    return sf::Vector2i(
        (int)sprite.getPosition().x / grid_size_i,
        (int)sprite.getPosition().y / grid_size_i);
}

const sf::Vector2f Entity::getSize()
{
    if (hitboxComponent)
    {
        return sf::Vector2f(
            hitboxComponent->getSize().x,
            hitboxComponent->getSize().y);
    }
    else
    {
        return sf::Vector2f(
            sprite.getGlobalBounds().width,
            sprite.getGlobalBounds().height);
    }
}

const sf::FloatRect Entity::getGlobalBounds()
{
    if (hitboxComponent)
        return hitboxComponent->getGlobalBounds();
    else
        return sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float &dt)
{
    if (hitboxComponent && movementComponent)
        return hitboxComponent->getNextPositionBounds(movementComponent->getVelocity(), dt);
    else
        return sf::FloatRect();
}

const sf::Vector2f &Entity::getVelocity()
{
    return movementComponent->getVelocity();
}

const float &Entity::getMaxVelocity()
{
    return movementComponent->getMaxVelocity();
}

const std::string Entity::getDirection()
{
    if (movementComponent)
        return movementComponent->getDirection();
    else
        return "NONE";
}

const bool Entity::hasCollided(sf::FloatRect &frect)
{
    if (hitboxComponent)
        return hitboxComponent->intersects(frect);
    else
        return false;
}

/* MODIFIERS ==================================================================================================== */

void Entity::setPosition(const sf::Vector2f &position)
{
    if (hitboxComponent)
        hitboxComponent->setPosition(position);
    else
        sprite.setPosition(position);
}

void Entity::stopVelocity()
{
    if (movementComponent)
        movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
    if (movementComponent)
        movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
    if (movementComponent)
        movementComponent->stopVelocityY();
}
