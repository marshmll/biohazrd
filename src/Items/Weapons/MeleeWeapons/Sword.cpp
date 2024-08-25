#include "stdafx.h"
#include "Sword.h"

Sword::Sword(std::map<std::string, sf::Texture> &textures)
    : MeleeWeapon("Sword", 80, textures.at("SWORD"), 20, 5, 25, 30)
{
    weaponSprite.setOrigin(
        weaponSprite.getGlobalBounds().width / 2.f,
        weaponSprite.getGlobalBounds().height - 5.f);
}

Sword::~Sword()
{
}

void Sword::update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                   const sf::Vector2f entity_center, std::string entity_direction)
{
    float angle;
    sf::Vector2f position;

    if (entity_direction == "LEFT")
    {
        weaponSprite.setTextureRect(weaponHorizontalIntRect);
        angle = -90.f;
        position.x = entity_center.x;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "RIGHT")
    {
        weaponSprite.setTextureRect(weaponHorizontalIntRect);
        angle = 90.f;
        position.x = entity_center.x - 15.f;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "UP")
    {
        weaponSprite.setTextureRect(weaponUpIntRect);
        position.x = entity_center.x + entity_size.x / 2.f - 5.f;
        position.y = entity_center.y;
        angle = 0.f;
    }
    else if (entity_direction == "DOWN")
    {
        weaponSprite.setTextureRect(weaponDownIntRect);
        position.x = entity_center.x - entity_size.x / 2.f + 10.f;
        position.y = entity_center.y + 15.f;
        angle = 0.f;
    }

    weaponSprite.setPosition(position);
    weaponSprite.setRotation(angle);
}

void Sword::render(sf::RenderTarget &target, sf::Shader *shader)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", weaponSprite.getPosition());
        target.draw(weaponSprite, shader);
    }
    else
    {
        target.draw(weaponSprite);
    }
}

Sword *Sword::clone()
{
    return new Sword(*this);
}
