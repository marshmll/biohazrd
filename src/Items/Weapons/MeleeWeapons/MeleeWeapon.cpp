#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const string texture_path, const short unsigned value,
                         const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
                         const float knockback)

    : Weapon(ItemType::RANGED_WEAPON, texture_path, value,
             range, damage_min, damage_max, knockback)

{
}

MeleeWeapon::~MeleeWeapon()
{
}