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

    short unsigned range;
    short unsigned damageMin;
    short unsigned damageMax;

    float attackCooldown;
    float attackCooldownMax;
    float attackCooldownIncrementer;
    ;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================== */

    Weapon(const ItemType type, const std::string texture_path, const short unsigned value,
           const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
           const short unsigned attack_cooldown_max, const short unsigned attack_cooldown_incrementer);

    virtual ~Weapon();

    /* FUNCTIONS ================================================================================================ */

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual Weapon *clone() = 0;

    /* ACCESSORS ================================================================================================ */

    virtual const short unsigned &getRange() const;

    virtual const short unsigned &getDamageMin() const;

    virtual const short unsigned &getDamageMax() const;
};

#endif /* WEAPON_H_ */