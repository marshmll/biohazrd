/*
 * HitboxComponent.cpp
 *
 *  Created on: 22 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "HitboxComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

HitboxComponent::HitboxComponent(
    Sprite &sprite,
    const float offset_x, const float offset_y,
    const float width, const float height) : sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
    hitbox.setPosition(
        sprite.getPosition().x + offset_x,
        sprite.getPosition().y + offset_y);

    hitbox.setSize(Vector2f(width, height));

    hitbox.setFillColor(Color::Transparent);

    hitbox.setOutlineThickness(-1.f);
    hitbox.setOutlineColor(Color::Green);

    nextPosition.width = width;
    nextPosition.height = height;
}

HitboxComponent::~HitboxComponent()
{
}

/* FUNCTIONS ==================================================================================================== */

void HitboxComponent::update()
{
    hitbox.setPosition(
        sprite.getPosition().x + offsetX,
        sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(RenderTarget &target)
{
    target.draw(hitbox);
}

/* ACCESSORS ==================================================================================================== */

const Vector2f &HitboxComponent::getPosition() const
{
    return hitbox.getPosition();
}

const Vector2f HitboxComponent::getCenteredPosition() const
{
    return Vector2f(
        hitbox.getPosition().x + (hitbox.getSize().x / 2.f),
        hitbox.getPosition().y + (hitbox.getSize().y / 2.f));
}

const Vector2f &HitboxComponent::getSize() const
{
    return hitbox.getSize();
}

const FloatRect HitboxComponent::getGlobalBounds() const
{
    return hitbox.getGlobalBounds();
}

const FloatRect HitboxComponent::getNextPositionBounds(const Vector2f &velocity, const float &dt)
{
    nextPosition.left = hitbox.getPosition().x + velocity.x * dt;
    nextPosition.top = hitbox.getPosition().y + velocity.y * dt;

    return nextPosition;
}

const bool HitboxComponent::intersects(FloatRect &frect) const
{
    return hitbox.getGlobalBounds().intersects(frect);
}

/* MODIFIERS ==================================================================================================== */

void HitboxComponent::setPosition(const Vector2f &position)
{
    hitbox.setPosition(position);
    sprite.setPosition(position.x - offsetX, position.y - offsetY);
}
