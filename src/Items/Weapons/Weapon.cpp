#include "stdafx.h"
#include "Weapon.h"

/* INITIALIZERS =============================================================================================== */

void Weapon::initVariables()
{
    cooldownTimer.restart();
    cooldownTimerMax = sf::Int32(700);
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

Weapon::Weapon(const ItemType type, const std::string texture_path, const unsigned short value,
               const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
               const unsigned short knockback)

    : Item(value, type)
{
    this->range = range;
    this->damageMin = damage_min;
    this->damageMax = damage_max;
    this->knockback = knockback;

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

const unsigned short &Weapon::getRange() const
{
    return range;
}

const unsigned short &Weapon::getDamageMin() const
{
    return damageMin;
}

const unsigned short &Weapon::getDamageMax() const
{
    return damageMax;
}

const unsigned short Weapon::getDamage() const
{
    return (rand() % damageMax - damageMin) + damageMin;
}

const unsigned short &Weapon::getKnockback() const
{
    return knockback;
}

const bool Weapon::didCooldown(const bool reset_timer)
{
    if (cooldownTimer.getElapsedTime().asMilliseconds() >= cooldownTimerMax)
    {
        if (reset_timer)
            cooldownTimer.restart();

        return true;
    }

    return false;
}

const sf::Int32 Weapon::getCurrentCooldownTimerValue() const
{
    return cooldownTimer.getElapsedTime().asMilliseconds();
}

const sf::Int32 &Weapon::getCooldownTimerMax() const
{
    return cooldownTimerMax;
}

/* MODIFIERS ===================================================================================================== */

void Weapon::setCooldownTimerMax(const sf::Int32 new_timer_max)
{
    cooldownTimerMax = new_timer_max;
}
