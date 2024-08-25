#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const std::string name, const unsigned short value, sf::Texture &texture,
                         const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
                         const unsigned short knockback)

    : Weapon(name, value, ItemType::MELEE_WEAPON, texture, range, damage_min, damage_max, knockback)

{
}

MeleeWeapon::~MeleeWeapon()
{
}