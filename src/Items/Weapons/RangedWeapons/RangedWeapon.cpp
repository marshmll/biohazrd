#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(const std::string texture_path, const short unsigned value,
                           const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
                           const short unsigned attack_cooldown_max, const short unsigned attack_cooldown_incrementer)

    : Weapon(ItemType::RANGED_WEAPON, texture_path, value,
             range, damage_min, damage_max,
             attack_cooldown_max, attack_cooldown_incrementer)
{
}

RangedWeapon::~RangedWeapon()
{
}