#ifndef MOVEMENTCOMPONENT_H_
#define MOVEMENTCOMPONENT_H_

enum States
{
    IDLE = 0,
    MOVING
};

enum Directions
{
    DOWN = 0,
    UP,
    RIGHT,
    LEFT
};

class MovementComponent
{
private:
    /* VARIABLES ================================================================================================= */

    sf::Sprite &sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;

    short unsigned state;
    short unsigned direction;

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);

    virtual ~MovementComponent();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Decelerates entity until it reaches 0 velocity.
     * @note -> Sets the movement state.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Moves a entity into some x and y direction.
     * @note -> Accelerates the entity until it reaches the max velocity.
     * @note -> Updates movement state.
     *
     * @return void
     */
    void move(const float dir_x, const float dir_y, const float &dt);

    /**
     * @brief Pushes the entity into some x and y directions.
     * @note -> Stops entity's velocity.
     * @note -> Sets velocity to the directions and strength.
     *
     * @return void
     */
    void knockback(const sf::Vector2f norm_vec, const float strength);

    /* ACCESSORS ================================================================================================= */

    /**
     * @return const sf::Vectorf&
     *
     * @brief Returns entity's current velocity.
     */
    const sf::Vector2f &getVelocity() const;

    /**
     * @brief Returns the entity max velocity.
     *
     * @return const float&
     */
    const float &getMaxVelocity() const;

    /**
     * @brief Returns current state.
     *
     * @return short unsigned&
     */
    const short unsigned &getCurrentState() const;

    /**
     * @brief Returns the current facing direction
     * @note Can return 4 strings:
     * @note -> "DOWN"
     * @note -> "UP"
     * @note -> "RIGHT"
     * @note -> "LEFT"
     *
     * @return std::string
     */
    const std::string getDirection() const;

    /**
     * @brief Returns the direction based on the key pressed.
     *
     * @return std::string
     */
    const std::string getKeyboardDirection() const;

    /* MODIFIERS ================================================================================================= */

    /**
     * @brief Resets the velocity to zero.
     *
     * @return void
     */
    void stopVelocity();

    /**
     * @brief Resets the x velocity to zero.
     *
     * @return void
     */
    void stopVelocityX();

    /**
     * @brief Resets the y velocity to zero.
     *
     * @return void
     */
    void stopVelocityY();
};

#endif /* MOVEMENTCOMPONENT_H_ */
