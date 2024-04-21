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

}

void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE_RIGHT", 100.f, 0, 0, 0, 0, 16.f, 18.f);
	this->animationComponent->addAnimation("IDLE_DOWN", 100.f, 0, 1, 0, 1, 16.f, 18.f);

	this->animationComponent->addAnimation("WALK_RIGHT", 20.f, 1, 0, 4, 0, 16.f, 18.f);
	this->animationComponent->addAnimation("WALK_DOWN", 20.f, 1, 1, 4, 1, 16.f, 18.f);
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

	this->createMovementComponent(180.f, 12.f, 6.f);
	this->createAnimationComponent(texture_sheet);

	this->initAnimations();
}

Player::~Player()
{

}

/* FUNCTIONS */
void Player::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Updates the player entity.
	 * -> Updates the movement component.
	 */

	this->movementComponent->update(dt);

	this->animationComponent->play("WALK_DOWN", dt);
}

