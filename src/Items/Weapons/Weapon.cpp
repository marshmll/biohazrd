#include "stdafx.h"
#include "Weapon.h"

/* INITIALIZERS =============================================================================================== */

void Weapon::initVariables()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

Weapon::Weapon(const short unsigned value, const ItemType type, const std::string texture_path)
    : Item(value, type)
{
    if (!weaponHorizontalTexture.loadFromFile(texture_path, sf::IntRect(0, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path + "\n");

    if (!weaponUpTexture.loadFromFile(texture_path, sf::IntRect(64, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path + "\n");

    if (!weaponDownTexture.loadFromFile(texture_path, sf::IntRect(128, 0, 64, 64)))
        ErrorHandler::throwErr("WEAPON::WEAPON::ERR_LOADING_TEXTURE::" + texture_path + "\n");

    weaponSprite.setTexture(weaponDownTexture);
}

Weapon::~Weapon()
{
}
