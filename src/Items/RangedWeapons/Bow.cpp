#include "stdafx.h"
#include "Bow.h"

Bow::Bow()
    : RangedWeapon(0)
{
}

Bow::~Bow()
{
}

void Bow::update()
{
}

void Bow::render()
{
}

Bow *Bow::clone()
{
    return new Bow(*this);
}
