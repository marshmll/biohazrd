#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
    : MeleeWeapon("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", 10,
                  80, 5, 15)
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
        weaponSprite.setTexture(weaponHorizontalTexture);
        angle = -90.f;
        position.x = entity_center.x;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "RIGHT")
    {
        weaponSprite.setTexture(weaponHorizontalTexture);
        angle = 90.f;
        position.x = entity_center.x - 15.f;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "UP")
    {
        weaponSprite.setTexture(weaponUpTexture);
        position.x = entity_center.x + entity_size.x / 2.f - 5.f;
        position.y = entity_center.y;
        angle = 0.f;
    }
    else if (entity_direction == "DOWN")
    {
        weaponSprite.setTexture(weaponDownTexture);
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
