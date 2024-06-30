#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const std::string texture_path, const unsigned short value,
                         const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
                         const unsigned short knockback)

    : Weapon(ItemType::RANGED_WEAPON, texture_path, value,
             range, damage_min, damage_max, knockback)

{
}

MeleeWeapon::~MeleeWeapon()
{
}