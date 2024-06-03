#include "stdafx.h"
#include "MovementComponent.h"

/* INITIALIZERS */

/* CONSTRUCTOR AND DESTRUCTOR */

MovementComponent::MovementComponent(
    sf::Sprite &sprite, float maxVelocity,
    float acceleration, float deceleration) : sprite(sprite), maxVelocity(maxVelocity),
                                              acceleration(acceleration), deceleration(deceleration),
                                              state(states::IDLE), direction(directions::DOWN)
{
}

MovementComponent::~MovementComponent()
{
}

/* FUNCTIONS */

void MovementComponent::update(const float &dt)
{
    /* Deceleration */

    // If player is moving right
    if (this->velocity.x >= 0.f)
    {
        // Decrease velocity
        this->velocity.x -= this->deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (this->velocity.x < 0.f)
            this->velocity.x = 0.f;
    }
    // If player is moving left
    else if (this->velocity.x <= 0.f)
    {
        // Decrease velocity
        this->velocity.x += this->deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (this->velocity.x > 0.f)
            this->velocity.x = 0.f;
    }

    // If player is moving down
    if (this->velocity.y >= 0.f)
    {
        // Decrease velocity
        this->velocity.y -= this->deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;
    }
    // If player is moving up
    else if (this->velocity.y <= 0.f)
    {
        // Decrease velocity
        this->velocity.y += this->deceleration * dt;

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
    /* Acceleration */

    // Accelerate player x
    this->velocity.x += this->acceleration * dir_x * dt;

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
    this->velocity.y += this->acceleration * dir_y * dt;

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

    else if (yDirection == 1 && this->velocity.x == 0)

        this->direction = DOWN;

    else if (yDirection == -1 && this->velocity.x == 0)

        this->direction = UP;
}

/* ACCESSORS */
const sf::Vector2f &MovementComponent::getVelocity() const
{
    return this->velocity;
}

const float &MovementComponent::getMaxVelocity() const
{
    return this->maxVelocity;
}

const short unsigned &MovementComponent::getCurrentState() const
{
    return this->state;
}

const std::string MovementComponent::getDirection() const
{
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

const std::string MovementComponent::getKeyboardDirection() const
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        return "UP";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return "DOWN";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        return "LEFT";
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return "RIGHT";
    else
        return "NONE";
}

/* MODIFIERS */

void MovementComponent::stopVelocity()
{
    this->velocity = sf::Vector2f(0.f, 0.f);
}

void MovementComponent::stopVelocityX()
{
    this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
    this->velocity.y = 0.f;
}
