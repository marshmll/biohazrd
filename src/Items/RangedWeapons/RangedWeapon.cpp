#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(const short unsigned value)
    : Item(value, ItemType::RANGED_WEAPON)
{
}

RangedWeapon::~RangedWeapon()
{
}