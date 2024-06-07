#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
    if (!this->weaponHorizontalTexture.loadFromFile("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", sf::IntRect(0, 0, 64, 64)))
        ErrorHandler::throwErr("PLAYER::PLAYER::ERR_LOADING_WEAPON_TEXTURE\n");

    if (!this->weaponUpTexture.loadFromFile("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", sf::IntRect(64, 0, 64, 64)))
        ErrorHandler::throwErr("PLAYER::PLAYER::ERR_LOADING_WEAPON_TEXTURE\n");

    if (!this->weaponDownTexture.loadFromFile("Assets/Images/Sprites/Player/pickaxe_spritesheet.png", sf::IntRect(128, 0, 64, 64)))
        ErrorHandler::throwErr("PLAYER::PLAYER::ERR_LOADING_WEAPON_TEXTURE\n");

    this->weaponSprite.setTexture(this->weaponDownTexture);

    this->weaponSprite.setOrigin(
        this->weaponSprite.getGlobalBounds().width / 2.f,
        this->weaponSprite.getGlobalBounds().height - 5.f);
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
        this->weaponSprite.setTexture(this->weaponHorizontalTexture);
        angle = -90.f;
        position.x = entity_center.x;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "RIGHT")
    {
        this->weaponSprite.setTexture(this->weaponHorizontalTexture);
        angle = 90.f;
        position.x = entity_center.x - 15.f;
        position.y = entity_center.y - 10.f;
    }
    else if (entity_direction == "UP")
    {
        this->weaponSprite.setTexture(this->weaponUpTexture);
        position.x = entity_center.x + entity_size.x / 2.f - 5.f;
        position.y = entity_center.y;
        angle = 0.f;
    }
    else if (entity_direction == "DOWN")
    {
        this->weaponSprite.setTexture(this->weaponDownTexture);
        position.x = entity_center.x - entity_size.x / 2.f + 10.f;
        position.y = entity_center.y + 15.f;
        angle = 0.f;
    }

    this->weaponSprite.setPosition(position);
    this->weaponSprite.setRotation(angle);
}

void Sword::render(sf::RenderTarget &target, sf::Shader *shader)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", this->weaponSprite.getPosition());
        target.draw(this->weaponSprite, shader);
    }
    else
    {
        target.draw(this->weaponSprite);
    }
}
