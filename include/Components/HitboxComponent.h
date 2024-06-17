#ifndef HITBOXCOMPONENT_H_
#define HITBOXCOMPONENT_H_

class HitboxComponent
{
private:
    /* VARIABLES ========================================================================================== */

    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;

    float offsetX;
    float offsetY;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ========================================================================= */

    /**
     * @brief Creates a hitbox component for a entity.
     * @note -> Sets position
     * @note -> Sets size
     * @note -> Sets fill color to transparent
     */
    HitboxComponent(sf::Sprite &sprite,
                    const float offset_x, const float offset_y,
                    const float width, const float height);

    virtual ~HitboxComponent();

    /* FUNCTIONS ========================================================================================== */

    /**
     * @brief Updates the hitbox positions based on the sprite position.
     *
     * @return void
     */
    void update();

    /**
     * @brief Renders the hitbox into a target.
     *
     * @return void
     */
    void render(sf::RenderTarget &target);

    /* ACCESSORS ========================================================================================== */

    /**
     * @brief Returns the hitbox position
     *
     * @return const sf::Vector2f&
     */
    const sf::Vector2f &getPosition() const;

    /**
     * @brief Returns the hitbox's center position.
     *
     * @return const sf::Vector2f
     */
    const sf::Vector2f getCenteredPosition() const;

    /**
     * @brief Returns the hitbox size
     *
     * @return const sf::Vector2f&
     */
    const sf::Vector2f &getSize() const;

    /**
     * @brief Returns the hitbox's global bounds
     *
     * @return sf::Vector2f&
     */
    const sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Returns the next position's global bounds.
     *
     * @param velocity The velocity to be used in the next position bounds calculation.
     * @param dt The game delta time.
     *
     * @return sf::FloatRect
     */
    const sf::FloatRect getNextPositionBounds(const sf::Vector2f &velocity, const float &dt);

    /**
     * @brief Checks if the hitbox has intersected some other object
     * (an sf::FloatRect).
     *
     * @return const bool
     */
    const bool intersects(sf::FloatRect &frect) const;

    /* MODIFIERS ========================================================================================== */

    /**
     * @brief Sets the hitbox position, and sets the sprite position
     * with the offsets.
     *
     * @return void
     */
    void setPosition(const sf::Vector2f &position);
};

#endif /* HITBOXCOMPONENT_H_ */
