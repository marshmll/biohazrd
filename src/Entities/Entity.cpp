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
    // aiComponent = nullptr;
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
    // delete aiComponent;
}
/* COMPONENT FUNCTIONS ========================================================================================== */

void Entity::setTexture(Texture &texture)
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

void Entity::createAnimationComponent(Texture &texture_sheet)
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

// void Entity::createAIComponent(Entity *target_entity)
// {
//     aiComponent = new AIComponent(*this, target_entity);
// }

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

const Vector2f &Entity::getPosition()
{
    if (hitboxComponent)
        return hitboxComponent->getPosition();

    return sprite.getPosition();
}

const Vector2f Entity::getCenteredPosition()
{
    if (hitboxComponent)

        return hitboxComponent->getCenteredPosition();

    return Vector2f(
        sprite.getPosition().x + sprite.getGlobalBounds().width / 2,
        sprite.getPosition().y + sprite.getGlobalBounds().height / 2);
}

const Vector2i Entity::getGridPosition(const int grid_size_i) const
{
    if (hitboxComponent)
        return Vector2i(
            (int)hitboxComponent->getCenteredPosition().x / grid_size_i,
            (int)hitboxComponent->getCenteredPosition().y / grid_size_i);

    return Vector2i(
        (int)sprite.getPosition().x / grid_size_i,
        (int)sprite.getPosition().y / grid_size_i);
}

const Vector2f Entity::getSize()
{
    if (hitboxComponent)
    {
        return Vector2f(
            hitboxComponent->getSize().x,
            hitboxComponent->getSize().y);
    }
    else
    {
        return Vector2f(
            sprite.getGlobalBounds().width,
            sprite.getGlobalBounds().height);
    }
}

const FloatRect Entity::getGlobalBounds()
{
    if (hitboxComponent)
        return hitboxComponent->getGlobalBounds();
    else
        return sprite.getGlobalBounds();
}

const FloatRect Entity::getNextPositionBounds(const float &dt)
{
    if (hitboxComponent && movementComponent)
        return hitboxComponent->getNextPositionBounds(movementComponent->getVelocity(), dt);
    else
        return FloatRect();
}

const Vector2f &Entity::getVelocity()
{
    return movementComponent->getVelocity();
}

const float &Entity::getMaxVelocity()
{
    return movementComponent->getMaxVelocity();
}

const string Entity::getDirection()
{
    if (movementComponent)
        return movementComponent->getDirection();
    else
        return "NONE";
}

const Vector2f Entity::getDistanceFrom(const Vector2f &point)
{
    Vector2f distance;

    distance.x = abs(this->getCenteredPosition().x - point.x);
    distance.y = abs(this->getCenteredPosition().y - point.y);

    return distance;
}

const float Entity::getRangeDistanceFrom(Entity &entity)
{
    Vector2f this_center = this->getCenteredPosition();
    Vector2f entity_center = entity.getCenteredPosition();

    // Dxy = sqrt((x2 - x1)^2 + (y2 - y1)^2)
    float distance = static_cast<float>(sqrt(pow(entity_center.x - this_center.x, 2.f) + pow(entity_center.y - this_center.y, 2.f)));

    return distance;
}

const bool Entity::hasCollided(FloatRect &frect)
{
    if (hitboxComponent)
        return hitboxComponent->intersects(frect);
    else
        return false;
}

const bool Entity::isDead()
{
    if (attributeComponent)
        return attributeComponent->isDead();
    else
        ErrorHandler::printErr("ENTITY::ISDEAD::WARNING_NULLPTR_ATTRIBUTECOMPONENT");

    return false;
}

/* MODIFIERS ==================================================================================================== */

void Entity::setPosition(const Vector2f &position)
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
    else
        ErrorHandler::printErr("ENTITY::STOPVELOCITY::WARNING_NULLPTR_MOVEMENTCOMPONENT");
}

void Entity::stopVelocityX()
{
    if (movementComponent)
        movementComponent->stopVelocityX();
    else
        ErrorHandler::printErr("ENTITY::STOPVELOCITYX::WARNING_NULLPTR_MOVEMENTCOMPONENT");
}

void Entity::stopVelocityY()
{
    if (movementComponent)
        movementComponent->stopVelocityY();
    else
        ErrorHandler::printErr("ENTITY::STOPVELOCITYY::WARNING_NULLPTR_MOVEMENTCOMPONENT");
}
