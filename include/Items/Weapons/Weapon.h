#ifndef WEAPON_H_
#define WEAPON_H_

#include "Item.h"

class Weapon : public Item
{
private:
    /* INITIALIZERS ============================================================================================ */

    void initVariables();

protected:
    /* PROTECTED VARIABLES ===================================================================================== */

    Texture weaponUpTexture;
    Texture weaponDownTexture;
    Texture weaponHorizontalTexture;
    Sprite weaponSprite;

    short unsigned range;
    short unsigned damageMin;
    short unsigned damageMax;
    float knockback;

    Clock cooldownTimer;
    Int32 cooldownTimerMax;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================== */

    Weapon(const ItemType type, const string texture_path, const short unsigned value,
           const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
           const float knockback);

    virtual ~Weapon();

    /* FUNCTIONS ================================================================================================ */

    virtual void update(const Vector2f &mouse_pos_view, const Vector2f entity_size,
                        const Vector2f entity_center, string entity_direction) = 0;

    virtual void render(RenderTarget &target, Shader *shader = nullptr) = 0;

    virtual Weapon *clone() = 0;

    /* ACCESSORS ================================================================================================ */

    const short unsigned &getRange() const;

    const short unsigned getDamage();

    const short unsigned &getDamageMin() const;

    const short unsigned &getDamageMax() const;

    const float &getKnockback() const;

    const bool didCooldown(const bool reset_timer = true);

    const Int32 getCurrentCooldownTimerValue() const;

    const Int32 &getCooldownTimerMax() const;

    /* MODIFIERS ================================================================================================ */

    void setCooldownTimerMax(const Int32 new_timer_max);
};

#endif /* WEAPON_H_ */