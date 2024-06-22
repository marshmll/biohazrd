/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */

Tile::Tile(
    const TileType type,
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const sf::Texture &texture, const sf::IntRect texture_rect,
    const bool collision,
    const float coll_box_width, const float coll_box_height,
    const float coll_box_offset_x, const float coll_box_offset_y)

    : type(type), collision(collision),
      collBoxOffsetX(coll_box_offset_x), collBoxOffsetY(coll_box_offset_y)
{
    tile.setTexture(texture);
    tile.setPosition(grid_x * grid_size_f, grid_y * grid_size_f);
    tile.setTextureRect(texture_rect);

    collBox.setSize(sf::Vector2f(coll_box_width, coll_box_height));
    collBox.setPosition((grid_x * grid_size_f) + coll_box_offset_x, (grid_y * grid_size_f) + coll_box_offset_y);
    collBox.setFillColor(sf::Color(255, 0, 0, 100));
    collBox.setOutlineThickness(1.f);
    collBox.setOutlineColor(sf::Color(255, 0, 0, 150));
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
}

const bool Tile::intersects(const sf::FloatRect &bounds) const
{
    return collBox.getGlobalBounds().intersects(bounds);
}

/* ACCESSORS */

const sf::Vector2f &Tile::getPosition() const
{
    return tile.getPosition();
}

const sf::IntRect &Tile::getTextureRect() const
{
    return tile.getTextureRect();
}

const bool &Tile::isCollideable() const
{
    return collision;
}

const sf::RectangleShape &Tile::getCollisionBox() const
{
    return collBox;
}

const TileType &Tile::getType() const
{
    return type;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
    return collBox.getGlobalBounds();
}
