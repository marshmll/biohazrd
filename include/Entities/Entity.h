#ifndef ENTITY_H_
#define ENTITY_H_

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class Entity
{
private:
    /* INITIALIZERS ============================================================================================== */

    /**
     * @brief Initializes entity components.
     *
     * @return void
     */
    virtual void initVariables();

protected:
    /* ENTITY SPRITE */
    Sprite sprite;

    /* ENTITY FUNCTIONAL COMPONENTS */
    HitboxComponent *hitboxComponent;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;
    AttributeComponent *attributeComponent;
    SkillComponent *skillComponent;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Creates a entity instance.
     * @note -> Initializes variables
     */
    Entity();

    /**
     * @brief Destructs entity instance.
     * @note -> Deletes all entity components
     */
    virtual ~Entity();

    /* COMPONENT FUNCTIONS ======================================================================================== */

    /**
     * @brief Sets texture for the entity sprite.
     * Scale sprites up.
     *
     * @return void
     */
    void setTexture(Texture &texture);

    /**
     * @brief Create a hitbox functionality component for the
     * entity.
     *
     * @return void
     */
    void createHitboxComponent(
        const float offset_x, const float offset_y,
        const float width, const float height);

    /**
     * @brief Creates a movement functionality component for the
     * entity.
     *
     * @return void
     */
    void createMovementComponent(
        const float max_velocity,
        const float acceleration, const float deceleration);

    /**
     * @brief Creates an animation functionality component for the
     * entity.
     *
     * @return void
     */
    void createAnimationComponent(Texture &texture_sheet);

    /**
     * @brief Creates an attribute functionality component for the
     * entity.
     *
     * @return void
     */
    void createAttributeComponent(const unsigned level);

    /**
     * @brief Creates an skill functionality component for the
     * entity
     *
     * @return void
     */
    void createSkillComponent();

    // /**
    //  * @brief Creates an Artificial Intelligence component for the
    //  * entity.
    //  *
    //  * @return void
    //  */
    // void createAIComponent(Entity *target_entity = nullptr);

    /* FUNCTIONS ================================================================================================== */

    /**
     * @brief Updates the entity.
     *
     * @return void
     */
    virtual void update(const float &dt, const Vector2f &mouse_pos_view = Vector2f()) = 0;

    /**
     * @brief Renders the entity into a target.
     * @note If a shader pointer is passed in, it will be used for rendering.
     *
     * @param target A render target reference.
     * @param show_hitbox Flag for rendering hitbox outine. (default: false)
     * @param shader A shader pointer. (default: nullptr)
     * @param light_pos The relative light position for shader rendering. (default Vector2f(0, 0))
     *
     * @return void
     */
    virtual void render(RenderTarget &target, const bool show_hitbox = false,
                        Shader *shader = nullptr, Vector2f light_pos = Vector2f()) = 0;

    /**
     * @brief Moves the movement component (whick moves the sprite) into some
     * x and y directions.
     * @note -> Checks if the entity can move first.
     *
     * @return void
     */
    virtual void move(const float dir_x, const float dir_y, const float &dt);

    virtual void knockback(const float dir_x, const float dir_y, const float strength);

    virtual void knockback(const Vector2f norm_vec, const float strength);

    /* ACCESSORS ================================================================================================= */

    /**
     * @brief Returns the position of the hitbox or the position
     * of the sprite, if there is no hitbox.
     *
     * @return const Vector2f&
     */
    virtual const Vector2f &getPosition();

    /**
     * @brief Returns the hitbox center position, or the sprite center
     * position if there is no hitbox.
     *
     * @return Vector2f
     */
    virtual const Vector2f getCenteredPosition();

    /**
     * @brief Returns the hitbox grid position, or the sprite grid
     * position if there is no hitbox.
     *
     * @return Vector2i
     */
    virtual const Vector2i getGridPosition(const int grid_size_i) const;

    /**
     * @brief Returns the hitbox size, or the sprite size
     * if there is not hitbox.
     *
     * @return const Vector2f
     */
    virtual const Vector2f getSize();

    /**
     * @brief Returns the hitbox bounds, or the sprite bounds
     * if there is not hitbox.
     *
     * @return const FloatRect
     */
    virtual const FloatRect getGlobalBounds();

    /**
     * @brief Returns the next global bounds based on the movement.
     *
     * @return FloatRect
     */
    virtual const FloatRect getNextPositionBounds(const float &dt);

    /**
     * @brief Returns the entity's current velocity.
     *
     * @return Vector2f&
     */
    virtual const Vector2f &getVelocity();

    /**
     * @brief Returns the entity's max velocity
     *
     * @return const float&
     */
    virtual const float &getMaxVelocity();

    /**
     * @brief Returns the entity's last direction.
     *
     * @return const string
     */
    virtual const string getDirection();

    /**
     * @brief Returns the x and y absolute distance between both entities.
     * @param point An Vector2f representing a single point.
     *
     * @return const Vector2f;
     */
    virtual const Vector2f getDistanceFrom(const Vector2f &point);

    /**
     * @brief Returns a single float value representing the absolute distance
     * between the centers of both entities.
     * @param entity An entity reference for calculating the distance.
     *
     * @return const float;
     */
    virtual const float getRangeDistanceFrom(Entity &entity);

    /**
     * @brief Returns if the entity's hitbox has intersected a FloatRect.
     * @note -> Returns false if the entity does not have a hitbox component.
     *
     * @return const bool
     */
    virtual const bool hasCollided(FloatRect &frect);

    /**
     * @brief Returns if the entity is dead.
     * @note -> Returns false and prints a warning if there
     * is no attribute component initialized for the entity.
     *
     * @return const bool
     */
    virtual const bool isDead();

    /* MODIFIERS ================================================================================================ */

    /**
     * @brief Sets a position to the entity's hitbox, or to
     * the entity's sprite, if there's no hitbox.
     *
     * @return void
     */
    virtual void setPosition(const Vector2f &position);

    /**
     * @brief Stops the entity's velocity
     *
     * @return void
     */
    virtual void stopVelocity();

    /**
     * @brief Stops the entity's x velocity
     *
     * @return void
     */
    virtual void stopVelocityX();

    /**
     * @brief Stops the entity's y velocity
     *
     * @return void
     */
    virtual void stopVelocityY();
};

#endif /* ENTITY_H_ */
