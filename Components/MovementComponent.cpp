#include "MovementComponent.h"

/* INITIALIZERS */

/* CONSTRUCTOR AND DESTRUCTOR */
MovementComponent::MovementComponent(sf::Sprite &sprite,
		float maxVelocity, float acceleration, float deceleration) :
		sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

/* FUNCTIONS */
void MovementComponent::update(const float &dt)
{
	/* Acceleration */

	// If player is moving right
	if (this->velocity.x >= 0.f)
	{
		// Decrease velocity
		this->velocity.x -= this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.x < 0)
			this->velocity.x = 0;
	}
	// If player is moving left
	else if (this->velocity.x <= 0.f)
	{
		// Decrease velocity
		this->velocity.x += this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.x > 0)
			this->velocity.x = 0;
	}

	// If player is moving down
	if (this->velocity.y >= 0.f)
	{
		// Decrease velocity
		this->velocity.y -= this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.y < 0)
			this->velocity.y = 0;
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

	// Final move
	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
	/*
	 * @return void
	 *
	 * Moves a entity into some x and y direction.
	 * -> Accelerates the entity until it reaches
	 * 	  the max velocity.
	 */

	/* Acceleration */

	// Accelerate player x
	this->velocity.x += this->acceleration * dir_x;

	// If player hits max velocity in x axis
	if (std::fabs(this->velocity.x) > this->maxVelocity)
	{
		// Get the direction coeficient (-1.0 or +1.0)
		float direction = this->velocity.x / std::fabs(this->velocity.x);

		// Keep the x velocity equal to max velocity.
		this->velocity.x = this->maxVelocity * direction;
	}

	// Accelerate player y
	this->velocity.y += this->acceleration * dir_y;

	// If player hits max velocity in y axis
	if (std::fabs(this->velocity.y) > this->maxVelocity)
	{
		// Get the direction coeficient (-1.0 or +1.0)
		float direction = this->velocity.y / std::fabs(this->velocity.y);

		// Keep the y velocity equal to max velocity.
		this->velocity.y = this->maxVelocity * direction;
	}
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
