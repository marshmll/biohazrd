#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:
protected:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    MeleeWeapon(const string texture_path, const short unsigned value,
                const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
                const float knockback);

    virtual ~MeleeWeapon();

    /* FUNCTIONS ============================================================================================== */

    virtual void update(const Vector2f &mouse_pos_view, const Vector2f entity_size,
                        const Vector2f entity_center, string entity_direction) = 0;

    virtual void render(RenderTarget &target, Shader *shader = nullptr) = 0;

    virtual MeleeWeapon *clone() = 0;
};

#endif /* MELEEWEAPON_H */