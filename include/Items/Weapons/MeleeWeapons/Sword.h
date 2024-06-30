#ifndef SWORD_H_
#define SWORD_H_

#include "MeleeWeapon.h"

class Sword : public MeleeWeapon
{
private:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    Sword();
    virtual ~Sword();

    /* FUNCTIONS ================================================================================================= */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction);

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr);

    virtual Sword *clone();
};

#endif /* SWORD_H */
