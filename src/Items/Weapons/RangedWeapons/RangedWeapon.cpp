#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(const short unsigned value, const std::string texture_path)
    : Weapon(value, ItemType::RANGED_WEAPON, texture_path)
{
}

RangedWeapon::~RangedWeapon()
{
}