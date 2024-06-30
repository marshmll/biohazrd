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

    sf::Texture weaponUpTexture;
    sf::Texture weaponDownTexture;
    sf::Texture weaponHorizontalTexture;
    sf::Sprite weaponSprite;

    unsigned short range;
    unsigned short damageMin;
    unsigned short damageMax;
    unsigned short knockback;

    sf::Clock cooldownTimer;
    sf::Int32 cooldownTimerMax;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================== */

    Weapon(const ItemType type, const std::string texture_path, const unsigned short value,
           const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
           const unsigned short knockback);

    virtual ~Weapon();

    /* FUNCTIONS ================================================================================================ */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual Weapon *clone() = 0;

    /* ACCESSORS ================================================================================================ */

    const unsigned short &getRange() const;

    const unsigned short &getDamageMin() const;

    const unsigned short &getDamageMax() const;

    const unsigned short getDamage() const;

    const unsigned short &getKnockback() const;

    const bool didCooldown(const bool reset_timer = true);

    const sf::Int32 getCurrentCooldownTimerValue() const;

    const sf::Int32 &getCooldownTimerMax() const;

    /* MODIFIERS ================================================================================================ */

    void setCooldownTimerMax(const sf::Int32 new_timer_max);
};

#endif /* WEAPON_H_ */