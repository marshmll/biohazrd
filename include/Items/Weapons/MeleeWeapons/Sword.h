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

    virtual void update(const Vector2f &mouse_pos_view, const Vector2f entity_size,
                        const Vector2f entity_center, string entity_direction);

    virtual void render(RenderTarget &target, Shader *shader = nullptr);

    virtual Sword *clone();
};

#endif /* SWORD_H */
