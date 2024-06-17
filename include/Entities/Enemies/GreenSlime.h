#ifndef GREENSLIME_H_
#define GREENSLIME_H_

#include "Enemy.h"

class Enemy;

class GreenSlime : public Enemy
{
private:
    /* INITIALIZERS ====================================================================== */

    void initVariables();

    void initAnimations();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ========================================================= */

    GreenSlime(const float x, const float y, sf::Texture &texture_sheet);

    virtual ~GreenSlime();

    /* FUNCTIONS ========================================================================== */

    void update(const float &dt, const sf::Vector2f &mouse_pos_view = sf::Vector2f());

    void render(sf::RenderTarget &target, const bool show_hitbox = false,
                sf::Shader *shader = nullptr, sf::Vector2f light_pos = sf::Vector2f());

    void updateAnimation(const float &dt);
};

#endif /* GREENSLIME_H_ */