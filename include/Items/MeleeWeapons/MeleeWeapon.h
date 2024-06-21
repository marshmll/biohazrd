#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H

#include "Item.h"

class Item;

class MeleeWeapon : public Item
{
private:
protected:
    sf::Texture weaponUpTexture;
    sf::Texture weaponDownTexture;
    sf::Texture weaponHorizontalTexture;
    sf::Sprite weaponSprite;

    int damageMin;
    int damageMax;

public:
    MeleeWeapon(const short unsigned value);

    virtual ~MeleeWeapon();

    virtual void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                        const sf::Vector2f entity_center, std::string entity_direction) = 0;

    virtual void render(sf::RenderTarget &target, sf::Shader *shader = nullptr) = 0;

    virtual MeleeWeapon *clone() = 0;
};

#endif /* MELEEWEAPON_H */