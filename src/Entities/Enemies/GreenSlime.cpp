#include "stdafx.h"
#include "GreenSlime.h"

/* INITIALIZERS =================================================================================================== */

void GreenSlime::initVariables()
{
}

void GreenSlime::initAnimations()
{
    animationComponent->addAnimation("IDLE", 9.f, 0, 0, 9, 0, 32.f, 32.f);
    animationComponent->addAnimation("GESTURE", 9.f, 0, 1, 9, 1, 32.f, 32.f);
    animationComponent->addAnimation("WALK", 6.f, 0, 2, 9, 2, 32.f, 32.f);
    animationComponent->addAnimation("ATTACK", 9.f, 0, 3, 9, 3, 32.f, 32.f);
    animationComponent->addAnimation("DEATH", 9.f, 0, 4, 9, 4, 32.f, 32.f);
}

/* CONSTRUCTOR AND DESTRUCTOR ====================================================================================== */

GreenSlime::GreenSlime(const float x, const float y, sf::Texture &texture_sheet)
    : Enemy(100)
{
    initVariables();
    setPosition(sf::Vector2f(x, y));

    createHitboxComponent(35.f, 70.f, 25.f, 25.f);
    createMovementComponent(100.f, 1000.f, 700.f);
    createAnimationComponent(texture_sheet);
    createAttributeComponent(1);

    initAnimations();
}

GreenSlime::~GreenSlime()
{
}

/* FUNCTIONS ======================================================================================================= */

void GreenSlime::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    movementComponent->update(dt);
    hitboxComponent->update();
    updateAnimation(dt);
}

void GreenSlime::render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader, sf::Vector2f light_pos)
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
    }

    if (show_hitbox)
        hitboxComponent->render(target);
}

void GreenSlime::updateAnimation(const float &dt)
{
    switch (movementComponent->getCurrentState())
    {
    case IDLE:
        animationComponent->play(
            "IDLE", dt);
        break;

    case MOVING:
        animationComponent->play(
            "WALK", dt,
            std::abs(movementComponent->getVelocity().x) + std::abs(movementComponent->getVelocity().y),
            movementComponent->getMaxVelocity(), PRIORITARY);
        break;
    }
}