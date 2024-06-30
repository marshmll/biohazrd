#include "stdafx.h"
#include "MovementComponent.h"

/* INITIALIZERS */

/* CONSTRUCTOR AND DESTRUCTOR */

MovementComponent::MovementComponent(
    sf::Sprite &sprite, float maxVelocity,
    float acceleration, float deceleration)

    : sprite(sprite), maxVelocity(maxVelocity),
      acceleration(acceleration), deceleration(deceleration),
      state(States::IDLE), direction(Directions::DOWN)
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
    if (velocity.x >= 0.f)
    {
        // Decrease velocity
        velocity.x -= deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (velocity.x < 0.f)
            velocity.x = 0.f;
    }
    // If player is moving left
    else if (velocity.x <= 0.f)
    {
        // Decrease velocity
        velocity.x += deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (velocity.x > 0.f)
            velocity.x = 0.f;
    }

    // If player is moving down
    if (velocity.y >= 0.f)
    {
        // Decrease velocity
        velocity.y -= deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (velocity.y < 0.f)
            velocity.y = 0.f;
    }
    // If player is moving up
    else if (velocity.y <= 0.f)
    {
        // Decrease velocity
        velocity.y += deceleration * dt;

        // If velocity hits 0, keep it at 0.
        if (velocity.y > 0)
            velocity.y = 0;
    }

    // Set state to idle
    if (velocity == sf::Vector2f(0, 0))
        state = IDLE;

    // Final move
    sprite.move(velocity * dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt)
{
    /* Acceleration */

    // Accelerate player x
    velocity.x += acceleration * dir_x * dt;

    // Get the x and y directions coeficients (-1.0 or +1.0)
    // +1.0 for DOWN and RIGHT.
    // -1.0 for UP and LEFT.
    float xDirection = velocity.x / std::fabs(velocity.x);
    float yDirection = velocity.y / std::fabs(velocity.y);

    // If player hits max velocity in x axis
    if (std::fabs(velocity.x) > maxVelocity)
    {
        // Keep the x velocity equal to max velocity.
        velocity.x = maxVelocity * xDirection;
    }

    // Accelerate player y
    velocity.y += acceleration * dir_y * dt;

    // If player hits max velocity in y axis
    if (std::fabs(velocity.y) > maxVelocity)
    {
        // Keep the y velocity equal to max velocity.
        velocity.y = maxVelocity * yDirection;
    }

    state = States::MOVING;

    // Update moving direction
    if (xDirection == 1 && velocity.y == 0)

        direction = Directions::RIGHT;

    else if (xDirection == -1 && velocity.y == 0)

        direction = Directions::LEFT;

    else if (yDirection == 1 && velocity.x == 0)

        direction = Directions::DOWN;

    else if (yDirection == -1 && velocity.x == 0)

        direction = Directions::UP;
}

/* ACCESSORS */
const sf::Vector2f &MovementComponent::getVelocity() const
{
    return velocity;
}

const float &MovementComponent::getMaxVelocity() const
{
    return maxVelocity;
}

const short unsigned &MovementComponent::getCurrentState() const
{
    return state;
}

const std::string MovementComponent::getDirection() const
{
    std::string direction;

    switch (this->direction)
    {
    case Directions::DOWN:
        direction = "DOWN";
        break;
    case Directions::UP:
        direction = "UP";
        break;
    case Directions::RIGHT:
        direction = "RIGHT";
        break;
    case Directions::LEFT:
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
    velocity = sf::Vector2f(0.f, 0.f);
}

void MovementComponent::stopVelocityX()
{
    velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
    velocity.y = 0.f;
}
