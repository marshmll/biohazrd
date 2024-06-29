#include "stdafx.h"
#include "Bow.h"

Bow::Bow()
    : RangedWeapon("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", 10,
                   200, 5, 50)
{
}

Bow::~Bow()
{
}

void Bow::update(const Vector2f &mouse_pos_view, const Vector2f entity_size, const Vector2f entity_center, std::string entity_direction)
{
}

void Bow::render(RenderTarget &target, Shader *shader)
{
}

Bow *Bow::clone()
{
    return new Bow(*this);
}
