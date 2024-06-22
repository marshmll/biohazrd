#include "stdafx.h"
#include "Item.h"

/* INITIALIZERS ================================================================================================ */

void Item::initVariables()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

Item::Item(const short unsigned value, const ItemType type)
{
    this->value = value;
    this->type = type;

    initVariables();
}

Item::~Item()
{
}
