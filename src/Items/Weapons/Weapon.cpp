#include "stdafx.h"
#include "Weapon.h"

/* INITIALIZERS =============================================================================================== */

void Weapon::initVariables()
{
    cooldownTimer.restart();
    cooldownTimerMax = sf::Int32(700);
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

Weapon::Weapon(const std::string name, const unsigned short value, const ItemType type,
               sf::Texture &texture,
               const unsigned short range, const unsigned short damage_min, const unsigned short damage_max,
               const unsigned short knockback)

    : Item(name, value, type, texture)
{
    this->range = range;
    this->damageMin = damage_min;
    this->damageMax = damage_max;
    this->knockback = knockback;

    initVariables();

    weaponHorizontalIntRect = sf::IntRect(64, 0, 64, 64);
    weaponUpIntRect = sf::IntRect(128, 0, 64, 64);
    weaponDownIntRect = sf::IntRect(192, 0, 64, 64);

    weaponSprite.setTexture(texture);
    weaponSprite.setTextureRect(weaponDownIntRect);
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
