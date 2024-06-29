#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(const string texture_path, const short unsigned value,
                           const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
                           const float knockback)

    : Weapon(ItemType::RANGED_WEAPON, texture_path, value,
             range, damage_min, damage_max, knockback)
{
}

RangedWeapon::~RangedWeapon()
{
}