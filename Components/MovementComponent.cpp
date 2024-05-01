#include "../PCH/stdafx.h"
#include "MovementComponent.h"

/* INITIALIZERS */

/* CONSTRUCTOR AND DESTRUCTOR */
MovementComponent::MovementComponent(sf::Sprite &sprite,
		float maxVelocity, float acceleration, float deceleration) :
		sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration),
				state(IDLE), direction(DOWN)
{

}

MovementComponent::~MovementComponent()
{

}

/* FUNCTIONS */
void MovementComponent::update(const float &dt)
{
	/**
	 * @return void
	 *
	 * Decelerates entity until it reaches 0 velocity.
	 * -> Sets the movement state.
	 */

	/* Deceleration */

	// If player is moving right
	if (this->velocity.x >= 0.f)
	{
		// Decrease velocity
		this->velocity.x -= this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;

	}
	// If player is moving left
	else if (this->velocity.x <= 0.f)
	{
		// Decrease velocity
		this->velocity.x += this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;

	}

	// If player is moving down
	if (this->velocity.y >= 0.f)
	{
		// Decrease velocity
		this->velocity.y -= this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;

	}
	// If player is moving up
	else if (this->velocity.y <= 0.f)
	{
		// Decrease velocity
		this->velocity.y += this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.y > 0)
			this->velocity.y = 0;

	}

	// Set state to idle
	if (this->velocity == sf::Vector2f(0, 0))
		this->state = IDLE;

	// Final move
	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
	/*
	 * @return void
	 *
	 * Moves a entity into some x and y direction.
	 * -> Accelerates the entity until it reaches the max velocity.
	 * -> Updates movement state.
	 */

	/* Acceleration */

	// Accelerate player x
	this->velocity.x += this->acceleration * dir_x;

	// Get the x and y directions coeficients (-1.0 or +1.0)
	// +1.0 for DOWN and RIGHT.
	// -1.0 for UP and LEFT.
	float xDirection = this->velocity.x / std::fabs(this->velocity.x);
	float yDirection = this->velocity.y / std::fabs(this->velocity.y);

	// If player hits max velocity in x axis
	if (std::fabs(this->velocity.x) > this->maxVelocity)
	{
		// Keep the x velocity equal to max velocity.
		this->velocity.x = this->maxVelocity * xDirection;
	}

	// Accelerate player y
	this->velocity.y += this->acceleration * dir_y;

	// If player hits max velocity in y axis
	if (std::fabs(this->velocity.y) > this->maxVelocity)
	{
		// Keep the y velocity equal to max velocity.
		this->velocity.y = this->maxVelocity * yDirection;
	}

	this->state = MOVING;

	// Update moving direction
	if (xDirection == 1 && this->velocity.y == 0)

		this->direction = RIGHT;

	else if (xDirection == -1 && this->velocity.y == 0)

		this->direction = LEFT;

	if (yDirection == 1 && this->velocity.x == 0)

		this->direction = DOWN;

	else if (yDirection == -1 && this->velocity.x == 0)

		this->direction = UP;
}

/* ACESSORS */
const sf::Vector2f& MovementComponent::getVelocity() const
{
	/**
	 * @return const sf::Vectorf&
	 *
	 * Returns entity's current velocity.
	 */

	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	/**
	 * @return const float&
	 *
	 * Returns the entity max velocity.
	 */

	return this->maxVelocity;
}

const short unsigned& MovementComponent::getCurrentState() const
{
	/**
	 * @return short unsigned&
	 *
	 * Returns current state.
	 */

	return this->state;
}

const std::string MovementComponent::getDirection() const
{
	/**
	 * @return std::string
	 *
	 * Returns the current facing direction
	 * Can return 4 strings:
	 * -> "DOWN"
	 * -> "UP"
	 * -> "RIGHT"
	 * -> "LEFT"
	 */

	std::string direction;

	switch (this->direction)
	{
	case DOWN:
		direction = "DOWN";
		break;
	case UP:
		direction = "UP";
		break;
	case RIGHT:
		direction = "RIGHT";
		break;
	case LEFT:
		direction = "LEFT";
		break;
	}

	return direction;
}
