/*
 * The player entity class.
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "Player.h"

/* INITIALIZERS ================================================================================================ */

void Player::initVariables()
{
}

void Player::initAnimations()
{
    animationComponent->addAnimation("IDLE_DOWN", 100.f, 0, 0, 0, 0, 64.f, 64.f);
    animationComponent->addAnimation("IDLE_UP", 100.f, 0, 1, 0, 1, 64.f, 64.f);
    animationComponent->addAnimation("IDLE_RIGHT", 100.f, 0, 2, 0, 2, 64.f, 64.f);
    animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 3, 0, 3, 64.f, 64.f);

    animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 4, 5, 4, 64.f, 64.f);
    animationComponent->addAnimation("WALK_UP", 11.f, 0, 5, 5, 5, 64.f, 64.f);
    animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 6, 5, 6, 64.f, 64.f);
    animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 7, 5, 7, 64.f, 64.f);

    animationComponent->addAnimation("SPRINT_DOWN", 20.f, 6, 4, 9, 4, 64.f, 64.f);
    animationComponent->addAnimation("SPRINT_UP", 20.f, 6, 5, 9, 5, 64.f, 64.f);
    animationComponent->addAnimation("SPRINT_RIGHT", 20.f, 6, 6, 9, 6, 64.f, 64.f);
    animationComponent->addAnimation("SPRINT_LEFT", 20.f, 6, 7, 9, 7, 64.f, 64.f);

    animationComponent->addAnimation("JUMP_DOWN", 13.f, 5, 0, 8, 0, 64.f, 64.f);
    animationComponent->addAnimation("JUMP_UP", 13.f, 5, 1, 8, 1, 64.f, 64.f);
    animationComponent->addAnimation("JUMP_RIGHT", 13.f, 5, 2, 8, 2, 64.f, 64.f);
    animationComponent->addAnimation("JUMP_LEFT", 13.f, 5, 3, 8, 3, 64.f, 64.f);
}

void Player::initInventory()
{
    inventory = new Inventory(40);
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Player::Player(const float x, const float y, sf::Texture &texture_sheet)
    : Entity("Player")
{
    initVariables();
    setPosition(sf::Vector2f(x, y));

    createHitboxComponent(76.f, 120.f, 42.f, 12.f);
    createMovementComponent(180.f, 1000.f, 600.f, true, 2.f);
    createAnimationComponent(texture_sheet);
    createAttributeComponent(1);
    createSkillComponent();

    initAnimations();
    initInventory();
}

Player::~Player()
{
    delete inventory;
}

/* FUNCTIONS ==================================================================================================== */

void Player::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    movementComponent->update(dt);
    hitboxComponent->update();
    updateAnimation(dt);

    sword.update(mouse_pos_view, getSize(), getCenteredPosition(), getDirection());
}

void Player::render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader, sf::Vector2f light_pos)
{
    if (shader)
    {
        if (getDirection() == "LEFT" || getDirection() == "UP")
        {
            sword.render(target, shader);
        }

        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);
        target.draw(sprite, shader);

        if (getDirection() == "RIGHT" || getDirection() == "DOWN")
        {
            sword.render(target, shader);
        }
    }
    else
    {
        target.draw(sprite);
        sword.render(target);
    }

    if (show_hitbox)
        hitboxComponent->render(target);
}

void Player::updateAnimation(const float &dt)
{
    switch (movementComponent->getCurrentState())
    {
    case IDLE:
        animationComponent->play(
            "IDLE_" + movementComponent->getDirection(), dt);
        break;
    case MOVING:
        animationComponent->play(
            "WALK_" + movementComponent->getDirection(), dt,
            std::fabs(movementComponent->getVelocity().x + movementComponent->getVelocity().y) * .8f,
            movementComponent->getMaxVelocity());
        break;
    case SPRINTING:
        animationComponent->play(
            "SPRINT_" + movementComponent->getDirection(), dt,
            std::fabs(movementComponent->getVelocity().x + movementComponent->getVelocity().y) * .8f,
            movementComponent->getMaxVelocity());
        break;
    }
}

AttributeComponent *Player::getAttributeComponent()
{
    return attributeComponent;
}

Inventory *Player::getInventory() 
{
    return inventory;
}

Weapon *Player::getWeapon()
{
    return &sword;
}

const std::string Player::formatStringToCharTab()
{
    AttributeComponent *ac = attributeComponent;

    std::stringstream sstream;

    sstream << "Level: " << ac->level << "\n"
            << "Experience: " << ac->exp << "\n"
            << "Accuracy: " << ac->accuracy << "\n";

    return sstream.str();
}

void Player::earnHp(const short unsigned hp_amount)
{
    attributeComponent->earnHp(hp_amount);
}

void Player::loseHp(const short unsigned hp_amount)
{
    attributeComponent->loseHp(hp_amount);
}

void Player::earnExp(const short unsigned exp_amount)
{
    attributeComponent->earnExp(exp_amount);
}

void Player::loseExp(const short unsigned exp_amount)
{
    attributeComponent->loseExp(exp_amount);
}
