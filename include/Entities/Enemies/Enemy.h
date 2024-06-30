#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy : public Entity
{
private:
    /* VARIABLES ================================================================================================= */

    EnemySpawnerTile &enemySpawnerTile;
    short unsigned expDrop; // The amount of exp the enemy drops after death.

    /**
     * @brief Initializes enemy animations.
     *
     * @return void
     */
    virtual void initAnimations() = 0;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

    /**
     * @brief Enemy entity class constructor.
     * @param exp_drop  The amount of exp the enemy drops after death
     */
    Enemy(const std::string name, EnemySpawnerTile &enemy_spawner_tile, const short unsigned exp_drop);

    virtual ~Enemy();

    /* FUNCTIONS ================================================================================================= */

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

    /**
     * @brief Increases hp by a given amount.
     * @note -> Limits hp to hpMax
     *
     * @return void
     */
    void earnHp(const short unsigned hp_amount);

    /**
     * @brief Decreases hp by a given amount.
     * @note -> Limits hp to 0
     *
     * @return void
     */
    void loseHp(const short unsigned hp_amount);

    /* ACCESSORS ================================================================================================= */

    /**
     * @brief Returns the enemy's linked spawner tile.
     *
     * @return EnemySpawnerTile&
     */
    EnemySpawnerTile &getEnemySpawnerTile();

    /**
     * @brief Returns the amount of exp the enemy drops after death.
     *
     * @return const short unsigned
     */
    const short unsigned getExpDrop() const;

    /**
     * @brief Returns the enemy's attribute component, or nullptr
     * if not initialized.
     *
     * @note -> Prints a warning if the attribute component is nullptr.
     *
     * @return AttributeComponent*
     */
    const AttributeComponent *getAttributeComponent() const;
};

#endif /* ENEMY_H_ */