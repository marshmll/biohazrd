#ifndef ENTITY_H_
#define ENTITY_H_

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	/* INITIALIZERS */

	/**
	 * @brief Initializes entity components.
	 *
	 * @return void
	 */
	void initVariables();

protected:
	/* ENTITY SPRITE */
	sf::Sprite sprite;

	/* ENTITY FUNCTIONAL COMPONENTS */
	HitboxComponent *hitboxComponent;
	MovementComponent *movementComponent;
	AnimationComponent *animationComponent;

public:
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

	/* COMPONENT FUNCTIONS */

	/**
	 * @brief Sets texture for the entity sprite.
	 * Scale sprites up.
	 *
	 * @return void
	 */
	void setTexture(sf::Texture &texture);

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
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

	/**
	 * @brief Creates a animation functionality component for the
	 * entity.
	 *
	 * @return void
	 */
	void createAnimationComponent(sf::Texture &texture_sheet);

	/* FUNCTIONS */

	/**
	 * @brief Updates the entity.
	 *
	 * @return void
	 */
	virtual void update(const float &dt) = 0;

	/**
	 * @brief Renders the entity
	 *
	 * @return void
	 */
	virtual void render(sf::RenderTarget &target) = 0;

	/**
	 * @brief Moves the movement component (whick moves the sprite) into some
	 * x and y directions.
	 * @note -> Checks if the entity can move first.
	 *
	 * @return void
	 */
	virtual void move(const float x, const float y, const float &dt);

	/* ACCESSORS */

	/**
	 * @brief Returns the position of the hitbox or the position
	 * of the sprite, if there is no hitbox.
	 *
	 * @return const sf::Vector2f&
	 */
	virtual const sf::Vector2f &getPosition();

	/**
	 * @brief Returns the position of the center of the sprite.
	 *
	 * @return const sf::Vector2f
	 */
	virtual const sf::Vector2f getCenteredPosition();

	/**
	 * @brief Returns the grid position.
	 *
	 * @return sf::Vector2i
	 */
	virtual const sf::Vector2i getGridPosition(const unsigned gridSizeU) const;

	/**
	 * @brief Returns the hitbox size, or the sprite size
	 * if there is not hitbox.
	 *
	 * @return const sf::Vector2f
	 */
	virtual const sf::Vector2f getSize();

	/**
	 * @brief Returns the hitbox bounds, or the sprite bounds
	 * if there is not hitbox.
	 *
	 * @return const sf::FloatRect
	 */
	virtual const sf::FloatRect getGlobalBounds();

	/**
	 * @brief Returns the next global bounds based on the movement.
	 * 
	 * @return sf::FloatRect
	 */
	virtual const sf::FloatRect getNextPositionBounds();

	/**
	 * @brief Returns if the entity's hitbox has intersected a FloatRect.
	 * @note -> Returns false if the entity does not have a hitbox component.
	 *
	 * @return const bool
	 */
	virtual const bool hasCollided(sf::FloatRect &frect);

	/* MODIFIERS */

	/**
	 * @brief Sets a position to the entity's hitbox, or to
	 * the entity's sprite, if there's no hitbox.
	 *
	 * @return void
	 */
	virtual void setPosition(const sf::Vector2f &position);

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
