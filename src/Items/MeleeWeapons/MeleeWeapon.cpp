#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const short unsigned value)
    : Item(value, ItemType::MELEE_WEAPON)
{
}

MeleeWeapon::~MeleeWeapon()
{
}