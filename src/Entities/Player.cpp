/*
 * The player entity class.
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "Player.h"

/* INITIALIZERS */

void Player::initVariables()
{
}

void Player::initAnimations()
{
    this->animationComponent->addAnimation("IDLE_DOWN", 100.f, 0, 0, 0, 0, 64.f, 64.f);
    this->animationComponent->addAnimation("IDLE_UP", 100.f, 0, 1, 0, 1, 64.f, 64.f);
    this->animationComponent->addAnimation("IDLE_RIGHT", 100.f, 0, 2, 0, 2, 64.f, 64.f);
    this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 3, 0, 3, 64.f, 64.f);

    this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 4, 5, 4, 64.f, 64.f);
    this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 5, 5, 5, 64.f, 64.f);
    this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 6, 5, 6, 64.f, 64.f);
    this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 7, 5, 7, 64.f, 64.f);

    this->animationComponent->addAnimation("SPRINT_DOWN", 10.f, 6, 4, 9, 4, 64.f, 64.f);
    this->animationComponent->addAnimation("SPRINT_UP", 10.f, 6, 5, 9, 5, 64.f, 64.f);
    this->animationComponent->addAnimation("SPRINT_RIGHT", 10.f, 6, 6, 9, 6, 64.f, 64.f);
    this->animationComponent->addAnimation("SPRINT_LEFT", 10.f, 6, 7, 9, 7, 64.f, 64.f);

    this->animationComponent->addAnimation("JUMP_DOWN", 13.f, 5, 0, 8, 0, 64.f, 64.f);
    this->animationComponent->addAnimation("JUMP_UP", 13.f, 5, 1, 8, 1, 64.f, 64.f);
    this->animationComponent->addAnimation("JUMP_RIGHT", 13.f, 5, 2, 8, 2, 64.f, 64.f);
    this->animationComponent->addAnimation("JUMP_LEFT", 13.f, 5, 3, 8, 3, 64.f, 64.f);
}

void Player::initInventory()
{
    this->inventory = new Inventory(40);
}

/* CONSTRUCTOR AND DESTRUCTOR */

Player::Player(const float x, const float y, sf::Texture &texture_sheet)
{
    this->initVariables();
    this->setPosition(sf::Vector2f(x, y));

    this->createHitboxComponent(75.f, 90.f, 42.f, 42.f);
    this->createMovementComponent(180.f, 1200.f, 800.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent(1);
    this->createSkillComponent();

    this->initAnimations();
    this->initInventory();
}

Player::~Player()
{
    delete this->inventory;
}

/* FUNCTIONS */

void Player::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    this->movementComponent->update(dt);
    this->hitboxComponent->update();
    this->updateAnimation(dt);

    this->sword.update(mouse_pos_view, this->getSize(), this->getCenteredPosition(), this->getDirection());
}

void Player::render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader, sf::Vector2f light_pos)
{
    if (shader)
    {
        if (this->getDirection() == "LEFT" || this->getDirection() == "UP")
        {
            this->sword.render(target, shader);
        }

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);
        target.draw(this->sprite, shader);

        if (this->getDirection() == "RIGHT" || this->getDirection() == "DOWN")
        {
            this->sword.render(target, shader);
        }
    }
    else
    {
        target.draw(this->sprite);
        this->sword.render(target);
    }

    if (show_hitbox)
        this->hitboxComponent->render(target);
}

void Player::updateAnimation(const float &dt)
{
    switch (this->movementComponent->getCurrentState())
    {
    case IDLE:
        this->animationComponent->play(
            "IDLE_" + this->movementComponent->getDirection(), dt);
        break;
    case MOVING:
        this->animationComponent->play(
            "WALK_" + this->movementComponent->getDirection(), dt,
            std::abs(this->movementComponent->getVelocity().x + this->movementComponent->getVelocity().y) * .8f,
            this->movementComponent->getMaxVelocity());
        break;
    }
}

AttributeComponent *Player::getAttributeComponent()
{
    return this->attributeComponent;
}

/* MODIFIERS */

void Player::earnHp(const int hp_amount)
{
    this->attributeComponent->earnHp(hp_amount);
}

void Player::loseHp(const int hp_amount)
{
    this->attributeComponent->loseHp(hp_amount);
}

void Player::earnExp(const int exp_amount)
{
    this->attributeComponent->earnExp(exp_amount);
}

void Player::loseExp(const int exp_amount)
{
    this->attributeComponent->loseExp(exp_amount);
}
