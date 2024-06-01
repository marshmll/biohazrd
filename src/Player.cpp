/*
 * The player entity class.
 *
 *  Created on: 19 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "Player.h"

#define PRIORITARY true

/* INITIALIZERS */
void Player::initVariables()
{
	this->isJumping = false;
	this->currentJumpAnimationName = "NONE";
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

/* CONSTRUCTOR AND DESTRUCTOR */

Player::Player(float x, float y, sf::Texture &texture_sheet)
{
	this->initVariables();
	this->setPosition(sf::Vector2f(x, y));

	this->createHitboxComponent(75.f, 90.f, 42.f, 42.f);
	this->createMovementComponent(180.f, 1200.f, 800.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->initAnimations();

	if (!this->weaponVerticalTexture.loadFromFile("Assets/Images/Sprites/Player/pickaxe_vertical.png"))
		throw std::runtime_error("PLAYER::PLAYER::ERR_LOADING_WEAPON_TEXTURE");

	if (!this->weaponHorizontalTexture.loadFromFile("Assets/Images/Sprites/Player/pickaxe_horizontal.png"))
		throw std::runtime_error("PLAYER::PLAYER::ERR_LOADING_WEAPON_TEXTURE");

	this->weaponSprite.setTexture(this->weaponVerticalTexture);

	this->weaponSprite.setOrigin(
		this->weaponSprite.getGlobalBounds().width / 2.f,
		this->weaponSprite.getGlobalBounds().height - 5.f);
}

Player::~Player()
{
}

/* FUNCTIONS */

void Player::update(const float &dt, const sf::Vector2f &mouse_pos_view)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		this->attributeComponent->earnExp(20);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		this->attributeComponent->loseExp(20);

	this->movementComponent->update(dt);
	this->hitboxComponent->update();
	this->updateAnimation(dt);

	this->attributeComponent->updateStats();

	// float dx = mouse_pos_view.x - this->weaponSprite.getPosition().x;
	// float dy = mouse_pos_view.y - this->weaponSprite.getPosition().y;
	// float PI = 3.14159265359f;
	// float angle = atan2(dy, dx) * 180 / PI;

	float angle;
	sf::Vector2f position;

	if (this->getDirection() == "LEFT")
	{
		this->weaponSprite.setTexture(this->weaponHorizontalTexture);
		angle = -90.f;
		position.x = this->getCenteredPosition().x - 10.f;
		position.y = this->getCenteredPosition().y - 10.f;
	}
	else if (this->getDirection() == "RIGHT")
	{
		this->weaponSprite.setTexture(this->weaponHorizontalTexture);
		angle = 90.f;
		position.x = this->getCenteredPosition().x;
		position.y = this->getCenteredPosition().y - 10.f;
	}
	else if (this->getDirection() == "UP")
	{
		this->weaponSprite.setTexture(this->weaponVerticalTexture);
		position.x = this->getCenteredPosition().x + this->getSize().x / 2.f - 5.f;
		position.y = this->getCenteredPosition().y - 10.f;
		angle = 0.f;
	}
	else if (this->getDirection() == "DOWN")
	{
		this->weaponSprite.setTexture(this->weaponVerticalTexture);
		position.x = this->getCenteredPosition().x - this->getSize().x / 2.f + 5.f;
		position.y = this->getCenteredPosition().y;
		angle = 180.f;
	}

	this->weaponSprite.setPosition(position);
	this->weaponSprite.setRotation(angle);
}

void Player::render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader)
{
	if (shader)
	{

		if (this->getDirection() == "LEFT" || this->getDirection() == "UP")
		{
			shader->setUniform("hasTexture", true);
			shader->setUniform("lightPos", this->getCenteredPosition());
			target.draw(this->weaponSprite, shader);
		}

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenteredPosition());
		target.draw(this->sprite, shader);

		if (this->getDirection() == "RIGHT" || this->getDirection() == "DOWN")
		{
			shader->setUniform("hasTexture", true);
			shader->setUniform("lightPos", this->getCenteredPosition());
			target.draw(this->weaponSprite, shader);
		}
	}
	else
	{
		target.draw(this->sprite);
		target.draw(this->weaponSprite);
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

void Player::updateJump(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
	{
		this->isJumping = true;
		this->animationComponent->play("JUMP_" + this->movementComponent->getDirection(), dt, PRIORITARY);
		this->currentJumpAnimationName = "JUMP_" + this->movementComponent->getDirection();
	}

	if (this->currentJumpAnimationName != "NONE")
	{
		if (this->animationComponent->isAnimationDone(this->currentJumpAnimationName))
			this->isJumping = false;
	}
}

AttributeComponent *Player::getAttributeComponent()
{
	return this->attributeComponent;
}

/* MODIFIERS */

void Player::earnHp(const int hpAmount)
{
	this->attributeComponent->earnHp(hpAmount);
}

void Player::loseHp(const int hpAmount)
{
	this->attributeComponent->loseHp(hpAmount);
}

void Player::earnExp(const int expAmount)
{
	this->attributeComponent->earnExp(expAmount);
}

void Player::loseExp(const int expAmount)
{
	this->attributeComponent->loseExp(expAmount);
}
