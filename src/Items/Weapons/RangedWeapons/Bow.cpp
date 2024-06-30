#include "stdafx.h"
#include "Bow.h"

Bow::Bow()
    : RangedWeapon("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", 10,
                   200, 5, 50, 100)
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
