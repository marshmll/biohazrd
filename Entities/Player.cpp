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

}

void Player::initAnimations()
{
	/**
	 * @return void
	 *
	 * Initializes player animations.
	 */

	this->animationComponent->addAnimation("IDLE_RIGHT", 100.f, 0, 0, 0, 0, 16.f, 18.f);
	this->animationComponent->addAnimation("IDLE_DOWN", 100.f, 0, 1, 0, 1, 16.f, 18.f);
	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 2, 0, 2, 16.f, 18.f);
	this->animationComponent->addAnimation("IDLE_UP", 100.f, 0, 3, 0, 3, 16.f, 18.f);

	this->animationComponent->addAnimation("WALK_RIGHT", 15.f, 1, 0, 4, 0, 16.f, 18.f);
	this->animationComponent->addAnimation("WALK_DOWN", 15.f, 1, 1, 4, 1, 16.f, 18.f);
	this->animationComponent->addAnimation("WALK_LEFT", 15.f, 1, 2, 4, 2, 16.f, 18.f);
	this->animationComponent->addAnimation("WALK_UP", 15.f, 1, 3, 4, 3, 16.f, 18.f);
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

	this->createMovementComponent(200.f, 12.f, 8.f);
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

	if (this->movementComponent->isStateActive(IDLE))
		this->animationComponent->play("IDLE_DOWN", dt);

	else if (this->movementComponent->isStateActive(MV_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt);

	else if (this->movementComponent->isStateActive(MV_DOWN))
		this->animationComponent->play("WALK_DOWN", dt);

	else if (this->movementComponent->isStateActive(MV_LEFT))
		this->animationComponent->play("WALK_LEFT", dt);

	else if (this->movementComponent->isStateActive(MV_UP))
		this->animationComponent->play("WALK_UP", dt);
}

