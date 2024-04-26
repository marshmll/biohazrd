/*
 * The player entity class.
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "Player.h"

/* INITIALIZERS */
void Player::initVariables()
{
	/**
	 * @return void
	 *
	 * Initializes player variables.
	 */

	this->test = false;
}

void Player::initAnimations()
{
	/**
	 * @return void
	 *
	 * Initializes player animations.
	 */

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

	this->animationComponent->addAnimation("JUMP_DOWN", 12.f, 5, 0, 8, 0, 64.f, 64.f);
}

/* CONSTRUCTOR AND DESTRUCTOR */
Player::Player(float x, float y, sf::Texture &texture_sheet)
{
	/**
	 * @constructor
	 *
	 * Player entity class constructor.
	 * -> Initializes variables
	 * -> Sets the player position with x and y arguments.
	 * -> Initializes components
	 * -> Initializes animations
	 */

	this->initVariables();
	this->setPosition(x, y);

	this->createHitboxComponent(70.f, 45.f, 50.f, 85.f);
	this->createMovementComponent(160.f, 10.f, 7.f);
	this->createAnimationComponent(texture_sheet);

	this->initAnimations();
}

Player::~Player()
{
	/**
	 * @destructor
	 */
}

/* FUNCTIONS */
void Player::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player entity.
	 * -> Updates the movement component.
	 * -> Plays the respective animation.
	 */

	this->movementComponent->update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		this->test = true;

	if (this->test)
	{
		if (this->animationComponent->play("JUMP_DOWN", dt, true))
		{
			test = false;
		}
	}

	switch (this->movementComponent->getCurrentState())
	{
	case IDLE_DOWN:
		this->animationComponent->play("IDLE_DOWN", dt);
		break;
	case IDLE_UP:
		this->animationComponent->play("IDLE_UP", dt);
		break;
	case IDLE_RIGHT:
		this->animationComponent->play("IDLE_RIGHT", dt);
		break;
	case IDLE_LEFT:
		this->animationComponent->play("IDLE_LEFT", dt);
		break;
	case MV_DOWN:
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y,
				this->movementComponent->getMaxVelocity());
		break;
	case MV_UP:
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y,
				this->movementComponent->getMaxVelocity());
		break;
	case MV_RIGHT:
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x,
				this->movementComponent->getMaxVelocity());
		break;
	case MV_LEFT:
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x,
				this->movementComponent->getMaxVelocity());
		break;
	}

	this->hitboxComponent->update();
}

