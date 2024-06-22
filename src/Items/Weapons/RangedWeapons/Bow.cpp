#include "stdafx.h"
#include "Bow.h"

Bow::Bow()
    : RangedWeapon(0, "Assets/Images/Sprites/Player/pickaxe_spritesheet.png")
{
}

Bow::~Bow()
{
}

void Bow::update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size, const sf::Vector2f entity_center, std::string entity_direction)
{
}

void Bow::render(sf::RenderTarget &target, sf::Shader *shader)
{
}

Bow *Bow::clone()
{
    return new Bow(*this);
}
