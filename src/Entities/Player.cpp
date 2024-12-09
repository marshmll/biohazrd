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
    animationComponent->addAnimation("IDLE_DOWN", 40.f, 0, 0, 3, 0, 32.f, 32.f);
    animationComponent->addAnimation("IDLE_UP", 40.f, 0, 1, 3, 1, 32.f, 32.f);
    animationComponent->addAnimation("IDLE_RIGHT", 40.f, 0, 2, 3, 2, 32.f, 32.f);
    animationComponent->addAnimation("IDLE_LEFT", 40.f, 0, 3, 3, 3, 32.f, 32.f);

    animationComponent->addAnimation("WALK_DOWN", 17.f, 0, 4, 3, 4, 32.f, 32.f);
    animationComponent->addAnimation("WALK_UP", 17.f, 0, 5, 3, 5, 32.f, 32.f);
    animationComponent->addAnimation("WALK_RIGHT", 17.f, 0, 6, 3, 6, 32.f, 32.f);
    animationComponent->addAnimation("WALK_LEFT", 17.f, 0, 7, 3, 7, 32.f, 32.f);

    animationComponent->addAnimation("SPRINT_DOWN", 20.f, 0, 4, 3, 4, 32.f, 32.f);
    animationComponent->addAnimation("SPRINT_UP", 20.f, 0, 5, 3, 5, 32.f, 32.f);
    animationComponent->addAnimation("SPRINT_RIGHT", 20.f, 0, 6, 3, 6, 32.f, 32.f);
    animationComponent->addAnimation("SPRINT_LEFT", 20.f, 0, 7, 3, 7, 32.f, 32.f);
}

void Player::initInventory()
{
    inventory = new Inventory(40);

    inventory->add(&sword);
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Player::Player(const float x, const float y, std::map<std::string, sf::Texture> &textures)
    : Entity("Player"), sword(textures)
{
    initVariables();
    setPosition(sf::Vector2f(x, y));

    createHitboxComponent(33.f, 58.f, 30.f, 12.f);
    createMovementComponent(160.f, 1000.f, 600.f, true, 2.2f);
    createAnimationComponent(textures.at("PLAYER_SPRITESHEET"));
    createAttributeComponent(50);
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
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);
        target.draw(sprite, shader);
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
    {
        animationComponent->play(
            "IDLE_" + movementComponent->getDirection(), dt);
        break;
    }
    case MOVING:
    {
        animationComponent->reset("IDLE_" + movementComponent->getDirection());
        animationComponent->play(
            "WALK_" + movementComponent->getDirection(), dt,
            std::fabs(movementComponent->getVelocity().x + movementComponent->getVelocity().y) * .8f,
            movementComponent->getMaxVelocity());
        break;
    }
    case SPRINTING:
    {
        animationComponent->reset("IDLE_" + movementComponent->getDirection());
        animationComponent->play(
            "SPRINT_" + movementComponent->getDirection(), dt,
            std::fabs(movementComponent->getVelocity().x + movementComponent->getVelocity().y) * .8f,
            movementComponent->getMaxVelocity());
        break;
    }
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
