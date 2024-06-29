/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

Tile::Tile(
    const TileType type,
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const Texture &texture, const IntRect texture_rect,
    const bool collision,
    const float coll_box_width, const float coll_box_height,
    const float coll_box_offset_x, const float coll_box_offset_y)

    : type(type), gridSizeF(grid_size_f), collision(collision),
      collBoxOffsetX(coll_box_offset_x), collBoxOffsetY(coll_box_offset_y)
{
    tile.setTexture(texture);
    tile.setPosition(grid_x * grid_size_f, grid_y * grid_size_f);
    tile.setTextureRect(texture_rect);

    collBox.setSize(Vector2f(coll_box_width, coll_box_height));
    collBox.setPosition((grid_x * grid_size_f) + coll_box_offset_x, (grid_y * grid_size_f) + coll_box_offset_y);
    collBox.setFillColor(Color(255, 0, 0, 100));
    collBox.setOutlineThickness(1.f);
    collBox.setOutlineColor(Color(255, 0, 0, 150));
}

Tile::~Tile()
{
}

/* FUNCTIONS ===================================================================================================== */

void Tile::update()
{
}

void Tile::render(RenderTarget &target, Shader *shader, const Vector2f light_pos)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);

        target.draw(tile, shader);
    }
    else
    {
        target.draw(tile);
    }
}

const bool Tile::intersects(const FloatRect &bounds) const
{
    return collBox.getGlobalBounds().intersects(bounds);
}

/* ACCESSORS ===================================================================================================== */

const Vector2f &Tile::getPosition() const
{
    return tile.getPosition();
}

const Vector2f Tile::getCenteredPosition() const
{
    Vector2f center;

    center.x = tile.getPosition().x + gridSizeF / 2.f;
    center.x = tile.getPosition().y + gridSizeF / 2.f;

    return center;
}

const IntRect &Tile::getTextureRect() const
{
    return tile.getTextureRect();
}

const bool &Tile::isCollideable() const
{
    return collision;
}

const RectangleShape &Tile::getCollisionBox() const
{
    return collBox;
}

const TileType &Tile::getType() const
{
    return type;
}

const FloatRect Tile::getGlobalBounds() const
{
    return collBox.getGlobalBounds();
}
