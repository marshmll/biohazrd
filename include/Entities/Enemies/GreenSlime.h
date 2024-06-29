#ifndef GREENSLIME_H_
#define GREENSLIME_H_

#include "Enemy.h"

class GreenSlime : public Enemy
{
private:
    /* INITIALIZERS ============================================================================================== */

    /**
     * @brief Initializes all variables for the green Slime entity.
     *
     * @return void
     */
    void initVariables();

    /**
     * @brief Initializes all animations for the green Slime entity.
     *
     * @return void
     */
    void initAnimations();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

    GreenSlime(EnemySpawnerTile &enemy_spawner_tile, Entity &player,
               const float x, const float y, Texture &texture_sheet);

    virtual ~GreenSlime();

    /* FUNCTIONS ================================================================================================== */

    /**
     * @brief Updates the green slime entity.
     * @param dt The game delta time.
     * @param mouse_pos_view The mouse position relative to the view (optional).
     *
     * @return void
     */
    void update(const float &dt, const Vector2f &mouse_pos_view = Vector2f());

    /**
     * @brief Renders the slime into a target. Can use a shader.
     *
     * @param target The render target to be used.
     * @param show_hitbox A flag for showing hitbox outline (debug).
     * @param shader A shader pointer to be used. (default nullptr)
     * @param light_pos The light position relative to the slime. Needed if
     * using shaders.
     *
     * @return void
     */
    void render(RenderTarget &target, const bool show_hitbox = false,
                Shader *shader = nullptr, Vector2f light_pos = Vector2f());

    /**
     * @brief Updates the animations being played for the slime entity.
     *
     * @return void
     */
    void updateAnimation(const float &dt);

    void updateAIBehaviors(const float &dt);
};

#endif /* GREENSLIME_H_ */