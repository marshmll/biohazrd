#include "stdafx.h"
#include "Item.h"

/* INITIALIZERS ================================================================================================ */

void Item::initVariables()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

Item::Item(const std::string name, const unsigned short value,
           const ItemType type, sf::Texture &texture)

    : name(name), value(value), type(type), texture(texture)
{
    iconIntRect = sf::IntRect(0, 0, 64, 64);
}

Item::~Item()
{
}

const std::string &Item::getName() const
{
    return name;
}

const sf::Texture *Item::getTexture() const
{
    return &texture;
}

sf::IntRect Item::getIconIntRect() const
{
    return iconIntRect;
}
