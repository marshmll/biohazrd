#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy : public Entity
{
private:
    /* VARIABLES ==================================================================================== */

    // EnemySpawner &enemySpawner;

    /**
     * @brief Initializes enemy animations.
     *
     * @return void
     */
    virtual void initAnimations() = 0;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ==================================================================== */

    /**
     * @brief Enemy entity class constructor.
     * @note -> Initializes variables
     * @note -> Sets the enemy position with x and y arguments.
     * @note -> Initializes components
     * @note -> Initializes animations
     */
    Enemy();

    virtual ~Enemy();

    /* FUNCTIONS ==================================================================================== */

    /**
     * @brief Updates the enemy.
     *
     * @param dt The game delta time.
     * @param mouse_pos_view The mouse position relative to the view.
     *
     * @return void
     */
    virtual void update(const float &dt, const sf::Vector2f &mouse_pos_view = sf::Vector2f()) = 0;

    /**
     * @brief Renders the enemy into a target.
     *
     * @param target A sf::RenderTarget& to render the enemy.
     * @param show_hitbox A flag to enable hitbox debugging.
     * @param shader A shader pointer to use. Default is nullptr.
     *
     * @return void
     */
    virtual void render(sf::RenderTarget &target, const bool show_hitbox,
                        sf::Shader *shader = nullptr, sf::Vector2f light_pos = sf::Vector2f()) = 0;

    /**
     * @brief Updates the enemy's animations.
     *
     * @param dt The game delta time.
     *
     * @return void
     */
    virtual void updateAnimation(const float &dt) = 0;
};

#endif /* ENEMY_H_ */