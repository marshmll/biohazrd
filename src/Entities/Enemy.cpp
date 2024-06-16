#include "stdafx.h"
#include "Enemy.h"

/* INITIALIZERS */

void Enemy::initVariables()
{
}

void Enemy::initAnimations()
{
    this->animationComponent->addAnimation("IDLE", 9.f, 0, 0, 9, 0, 32.f, 32.f);
    this->animationComponent->addAnimation("GESTURE", 9.f, 0, 1, 9, 1, 32.f, 32.f);
    this->animationComponent->addAnimation("WALK", 6.f, 0, 2, 9, 2, 32.f, 32.f);
    this->animationComponent->addAnimation("ATTACK", 9.f, 0, 3, 9, 3, 32.f, 32.f);
    this->animationComponent->addAnimation("DEATH", 9.f, 0, 4, 9, 4, 32.f, 32.f);
}

/* CONSTRUCTOR AND DESTRUCTOR */

Enemy::Enemy(const float x, const float y, sf::Texture &texture_sheet)
{
    this->initVariables();
    this->setPosition(sf::Vector2f(x, y));

    this->createHitboxComponent(35.f, 70.f, 25.f, 25.f);
    this->createMovementComponent(100.f, 1000.f, 700.f);
    this->createAnimationComponent(texture_sheet);

    this->initAnimations();
}

Enemy::~Enemy()
{
}

/* FUNCTIONS */

void Enemy::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
    this->movementComponent->update(dt);
    this->hitboxComponent->update();
    this->updateAnimation(dt);
}

void Enemy::render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader, sf::Vector2f light_pos)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);

        target.draw(this->sprite, shader);
    }
    else
    {
        target.draw(this->sprite);
    }

    if (show_hitbox)
        this->hitboxComponent->render(target);
}

void Enemy::updateAnimation(const float &dt)
{
    switch (this->movementComponent->getCurrentState())
    {
    case IDLE:
        this->animationComponent->play("IDLE", dt);
        break;

    case MOVING:
        this->animationComponent->play("WALK", dt,
            std::abs(this->movementComponent->getVelocity().x) + std::abs(this->movementComponent->getVelocity().y),
            this->movementComponent->getMaxVelocity(), PRIORITARY);
        break;
    }
}