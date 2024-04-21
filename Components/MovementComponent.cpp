#include "MovementComponent.h"

/* INITIALIZERS */

/* CONSTRUCTOR AND DESTRUCTOR */
MovementComponent::MovementComponent(sf::Sprite &sprite,
		float maxVelocity, float acceleration, float deceleration) :
		sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration),
				movementState(IDLE)
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
		{
			this->velocity.x = 0.f;
		}
	}
	// If player is moving left
	else if (this->velocity.x <= 0.f)
	{
		// Decrease velocity
		this->velocity.x += this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	// If player is moving down
	if (this->velocity.y >= 0.f)
	{
		// Decrease velocity
		this->velocity.y -= this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	// If player is moving up
	else if (this->velocity.y <= 0.f)
	{
		// Decrease velocity
		this->velocity.y += this->deceleration;

		// If velocity hits 0, keep it at 0.
		if (this->velocity.y > 0)
		{
			this->velocity.y = 0;
		}
	}

	if (this->velocity == sf::Vector2f(0, 0))
		this->movementState = IDLE;

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
	 * -> Sets movement state.
	 */

	/* Acceleration */

	// Accelerate player x
	this->velocity.x += this->acceleration * dir_x;

	// Get the x and y directions coeficients (-1.0 or +1.0)
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

	if (xDirection == 1 && this->velocity.y == 0)
		this->movementState = MV_RIGHT;

	else if (xDirection == -1 && this->velocity.y == 0)
		this->movementState = MV_LEFT;

	if (yDirection == 1 && this->velocity.x == 0)
		this->movementState = MV_DOWN;

	else if (yDirection == -1 && this->velocity.x == 0)
		this->movementState = MV_UP;
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

const bool MovementComponent::isStateActive(const short unsigned state) const
{
	/**
	 * @return bool
	 *
	 * Verifies if a movement state is active.
	 */

	return this->movementState == state;
}
