#ifndef REGULARTILE_H_
#define REGULARTILE_H_

#include "Tile.h"

class RegularTile : public Tile
{
private:
public:
    /**
     * @brief The Regular Tile Class Constructor.
     *
     * @param type The tile type.
     * @param grid_x The x position relative to the grid.
     * @param grid_y The y position relative to the grid.
     * @param grid_size_f The grid size (float)
     * @param texture A sf::Texture reference.
     * @param texture_rect A sf::IntRect to crop the texture with.
     * @param collision Is the tile collideable?
     * @param coll_box_width The collision box width (default = 0.f)
     * @param coll_box_height The collision box height (default = 0.f)
     * @param coll_box_offset_x The collision box offset x (default = 0.f)
     * @param coll_box_offset_y The collision box offset y (default = 0.f)
     */
    RegularTile(
        const TileType type,
        const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
        const sf::Texture &texture, const sf::IntRect texture_rect, const bool collision,
        const float coll_box_width = 0.f, const float coll_box_height = 0.f,
        const float coll_box_offset_x = 0.f, const float coll_box_offset_y = 0.f);

    virtual ~RegularTile();

    void update();

    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    const std::string getPropertiesAsString() const;
};

#endif /* REGULARTILE_H_ */