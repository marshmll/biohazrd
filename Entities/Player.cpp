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

void Player::initComponents()
{
	this->createMovementComponent(100.f);
}

Player::Player(float x, float y, sf::Texture &texture)
{
	/**
	 * @constructor
	 *
	 * Player entity class constructor.
	 * -> Initializes variables
	 * -> Initializes components
	 * -> Sets player sprite texture.
	 * -> Sets the player position with x and y arguments.
	 */

	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

Player::~Player()
{

}

/* FUNCTIONS */

