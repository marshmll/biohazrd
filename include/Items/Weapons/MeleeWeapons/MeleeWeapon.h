#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:
protected:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    MeleeWeapon(const std::string texture_path, const unsigned short value,
                const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
                const unsigned short knockback);

    virtual ~MeleeWeapon();

    /* FUNCTIONS ============================================================================================== */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual MeleeWeapon *clone() = 0;
};

#endif /* MELEEWEAPON_H */