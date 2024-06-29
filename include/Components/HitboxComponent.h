#ifndef HITBOXCOMPONENT_H_
#define HITBOXCOMPONENT_H_

class HitboxComponent
{
private:
    /* VARIABLES =================================================================================================== */

    Sprite &sprite;
    RectangleShape hitbox;
    FloatRect nextPosition;

    float offsetX;
    float offsetY;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

    /**
     * @brief Creates a hitbox component for a entity.
     * @note -> Sets position
     * @note -> Sets size
     * @note -> Sets fill color to transparent
     */
    HitboxComponent(Sprite &sprite,
                    const float offset_x, const float offset_y,
                    const float width, const float height);

    virtual ~HitboxComponent();

    /* FUNCTIONS =================================================================================================== */

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
    void render(RenderTarget &target);

    /* ACCESSORS =================================================================================================== */

    /**
     * @brief Returns the hitbox position
     *
     * @return const Vector2f&
     */
    const Vector2f &getPosition() const;

    /**
     * @brief Returns the hitbox's center position.
     *
     * @return const Vector2f
     */
    const Vector2f getCenteredPosition() const;

    /**
     * @brief Returns the hitbox size
     *
     * @return const Vector2f&
     */
    const Vector2f &getSize() const;

    /**
     * @brief Returns the hitbox's global bounds
     *
     * @return Vector2f&
     */
    const FloatRect getGlobalBounds() const;

    /**
     * @brief Returns the next position's global bounds.
     *
     * @param velocity The velocity to be used in the next position bounds calculation.
     * @param dt The game delta time.
     *
     * @return FloatRect
     */
    const FloatRect getNextPositionBounds(const Vector2f &velocity, const float &dt);

    /**
     * @brief Checks if the hitbox has intersected some other object
     * (an FloatRect).
     *
     * @return const bool
     */
    const bool intersects(FloatRect &frect) const;

    /* MODIFIERS =================================================================================================== */

    /**
     * @brief Sets the hitbox position, and sets the sprite position
     * with the offsets.
     *
     * @return void
     */
    void setPosition(const Vector2f &position);
};

#endif /* HITBOXCOMPONENT_H_ */
