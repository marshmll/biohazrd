#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	/* VARIABLES */

	bool isJumping;
	std::string currentJumpAnimationName;

	/* INITIALIZERS */

	/**
	 * @brief Initializes player variables.
	 *
	 * @return void
	 */
	void initVariables();

	/**
	 * @brief Initializes player animations.
	 *
	 * @return void
	 */
	void initAnimations();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */

	/**
	 * @brief Player entity class constructor.
	 * @note -> Initializes variables
	 * @note -> Sets the player position with x and y arguments.
	 * @note -> Initializes components
	 * @note -> Initializes animations
	 */
	Player(float x, float y, sf::Texture &texture_sheet);

	/**
	 * @brief Player destructor
	 */
	virtual ~Player();

	/* FUNCTIONS */

	/**
	 * @brief Updates the player entity.
	 * @note -> Updates the movement component.
	 * @note -> Plays the respective animation.
	 *
	 * @return void
	 */
	void update(const float &dt);

	/**
	 * @brief Renders the player into a target.
	 *
	 * @return void
	 */
	void render(sf::RenderTarget &target, const bool show_hitbox = false, sf::Shader *shader = nullptr);

	/**
	 * @brief Updates the player animations.
	 *
	 * @return void
	 */
	void updateAnimation(const float &dt);

	/**
	 * @brief Updates the jump states and animations.
	 *
	 * @return void
	 */
	void updateJump(const float &dt);

	/* ACCESSORS */

	/**
	 * @brief Returns a pointer to the player's atribute component.
	 *
	 * @return AttributeComponent*
	 */
	AttributeComponent *getAttributeComponent();

	/* MODIFIERS */

	/**
	 * @brief Increases hp by a given amount.
	 * @note -> Limits hp to hpMax
	 *
	 * @return void
	 */
	void earnHp(const int hpAmount);

	/**
	 * @brief Decreases hp by a given amount.
	 * @note -> Limits hp to 0
	 *
	 * @return void
	 */
	void loseHp(const int hpAmount);

	/**
	 * @brief Increases exp by a given amount.
	 * @note -> Updates the level.
	 *
	 * @return void
	 */
	void earnExp(const int expAmount);

	/**
	 * @brief Decreases exp by a given amount.
	 * @note -> Limits exp to 0
	 *
	 * @return void
	 */
	void loseExp(const int expAmount);
};

#endif /* PLAYER_H_ */
