#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(const short unsigned value, const std::string texture_path)
    : Weapon(value, ItemType::MELEE_WEAPON, texture_path)
{
}

MeleeWeapon::~MeleeWeapon()
{
}