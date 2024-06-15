/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */

Tile::Tile(const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
           const sf::Texture &texture, const sf::IntRect texture_rect,
           const bool collision, const short type)
{
    this->tile.setTexture(texture);

    this->tile.setPosition(grid_x * grid_size_f, grid_y * grid_size_f);

    this->tile.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

Tile::~Tile()
{
}

/* FUNCTIONS */

void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);

        target.draw(this->tile, shader);
    }
    else
    {
        target.draw(this->tile);
    }
}

const bool Tile::intersects(const sf::FloatRect &bounds) const
{
    return this->tile.getGlobalBounds().intersects(bounds);
}

/* ACCESSORS */

const sf::Vector2f &Tile::getPosition() const
{
    return this->tile.getPosition();
}

const sf::IntRect &Tile::getTextureRect() const
{
    return this->tile.getTextureRect();
}

const bool &Tile::isCollideable() const
{
    return this->collision;
}

const short &Tile::getType() const
{
    return this->type;
}

const std::string Tile::getPropertiesAsString() const
{
    std::stringstream ss;

    ss << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " "
       << this->collision << " " << this->type;

    return ss.str();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return this->tile.getGlobalBounds();
}
