#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(
    const TileType type,
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const sf::Texture &texture, const sf::IntRect texture_rect, const bool collision,
    const float coll_box_width, const float coll_box_height,
    const float coll_box_offset_x, const float coll_box_offset_y)

    : Tile(type, grid_x, grid_y, grid_size_f,
           texture, texture_rect, collision,
           coll_box_width, coll_box_height,
           coll_box_offset_x, coll_box_offset_y)
{
}

RegularTile::~RegularTile()
{
}

void RegularTile::update()
{
}

void RegularTile::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
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

const std::string RegularTile::getPropertiesAsString() const
{
    std::stringstream properties;

    properties << this->type << " "
               << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " "
               << this->collision << " "
               << this->collBox.getSize().x << " " << this->collBox.getSize().y << " "
               << this->collBoxOffsetX << " " << this->collBoxOffsetY;

    return properties.str();
}
