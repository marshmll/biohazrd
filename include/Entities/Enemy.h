#ifndef ENEMY_H_
#define ENEMY_H_

#include "Entity.h"

class Enemy : public Entity
{
private:
    /* VARIABLES */

    /* INITIALIZERS */

    /**
     * @brief Initializes enemy variables.
     *
     * @return void
     */
    void initVariables();

    /**
     * @brief Initializes enemy animations.
     *
     * @return void
     */
    void initAnimations();

public:
    /* CONSTRUCTOR AND DESTRUCTOR */

    /**
     * @brief Enemy entity class constructor.
     * @note -> Initializes variables
     * @note -> Sets the enemy position with x and y arguments.
     * @note -> Initializes components
     * @note -> Initializes animations
     */
    Enemy(float x, float y, sf::Texture &texture_sheet);

    virtual ~Enemy();

    /* FUNCTIONS */

    void update(const float &dt, const sf::Vector2f &mouse_pos_view);
    void render(sf::RenderTarget &target, const bool show_hitbox, sf::Shader *shader = nullptr);

    void updateAnimation(const float &dt);
};

#endif /* ENEMY_H_ */