#include "stdafx.h"
#include "Weapon.h"

/* INITIALIZERS =============================================================================================== */

void Weapon::initVariables()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

Weapon::Weapon(const ItemType type, const std::string texture_path, const short unsigned value,
               const short unsigned range, const short unsigned damage_min, const short unsigned damage_max,
               const short unsigned attack_cooldown_max, const short unsigned attack_cooldown_incrementer)

    : Item(value, type)
{
    this->range = range;
    damageMin = damage_min;
    damageMax = damage_max;
    
    attackCooldown = 0.f;
    attackCooldownMax = attack_cooldown_max;
    attackCooldownIncrementer = attack_cooldown_incrementer;

    initVariables();

    if (!weaponHorizontalTexture.loadFromFile(texture_path, sf::IntRect(0, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    if (!weaponUpTexture.loadFromFile(texture_path, sf::IntRect(64, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    if (!weaponDownTexture.loadFromFile(texture_path, sf::IntRect(128, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path);

    weaponSprite.setTexture(weaponDownTexture);
}

Weapon::~Weapon()
{
}

/* ACCESSORS ================================================================================================ */

const short unsigned &Weapon::getRange() const
{
    return range;
}

const short unsigned &Weapon::getDamageMin() const
{
    return damageMin;
}

const short unsigned &Weapon::getDamageMax() const
{
    return damageMax;
}
