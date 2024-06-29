#ifndef BOW_H_
#define BOW_H_

#include "RangedWeapon.h"

class Bow : public RangedWeapon
{
private:
protected:
public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    Bow();

    virtual ~Bow();

    /* FUNCTIONS ================================================================================================= */

    void update(const Vector2f &mouse_pos_view, const Vector2f entity_size,
                const Vector2f entity_center, string entity_direction);

    void render(RenderTarget &target, Shader *shader = nullptr);

    Bow *clone();
};

#endif // BOW_H_
