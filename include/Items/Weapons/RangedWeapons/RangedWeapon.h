#ifndef RANGEDWEAPON_H_
#define RANGEDWEAPON_H_

#include "Weapon.h"

class RangedWeapon : public Weapon
{
private:
protected:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    RangedWeapon(const std::string name, const unsigned short value, sf::Texture &texture,
                 const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
                 const unsigned short knockback);

    virtual ~RangedWeapon();

    /* FUNCTIONS ============================================================================================== */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual RangedWeapon *clone() = 0;
};

#endif