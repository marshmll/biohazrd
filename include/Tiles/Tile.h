#ifndef TILE_H_
#define TILE_H_

enum TileType
{
    DEFAULT = 0,
    HARMFUL,
    DOODAD,
    SPAWNER // KEEP THIS AT LAST!
};

class Tile
{
protected:
    /* PROTECTED VARIABLES ==================================================================================== */

    sf::Sprite tile;
    TileType type;

    bool collision;

    sf::RectangleShape collBox;
    float collBoxOffsetX;
    float collBoxOffsetY;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    /**
     * @brief The Tile Class Constructor.
     *
     * @param type The tile type.
     * @param grid_x The x position relative to the grid.
     * @param grid_y The y position relative to the grid.
     * @param grid_size_f The grid size (float)
     * @param texture A sf::Texture reference.
     * @param texture_rect A sf::IntRect to crop the texture with.
     * @param collision Is the tile collideable?
     * @param coll_box_width The collision box width
     * @param coll_box_height The collision box height
     * @param coll_box_offset_x The collision box offset x
     * @param coll_box_offset_y The collision box offset y
     */
    Tile(const TileType type,
         const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
         const sf::Texture &texture, const sf::IntRect texture_rect, const bool collision,
         const float coll_box_width, const float coll_box_height,
         const float coll_box_offset_x, const float coll_box_offset_y);

    virtual ~Tile();

    /* FUNCTIONS ============================================================================================== */

    /**
     * @brief Updates the tile.
     *
     * @return void
     */
    virtual void update();

    /**
     * @brief Renders the tile into a target.
     * @note If a shader pointer is passed in, it will be used for rendering.
     *
     * @param target A render target reference.
     * @param shader A shader pointer. (optional)
     * @param light_pos The lighting position (needed if using shaders)
     *
     * @return void
     */
    virtual void render(sf::RenderTarget &target,
                        sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    /**
     * @brief Returns if the tile's collision box intersects a
     * given FloatRect.
     *
     * @return bool
     */
    const bool intersects(const sf::FloatRect &bounds) const;

    /* ACCESSORS ================================================================================================= */

    /**
     * @brief Returns the tile's sprite current position.
     *
     * @return const sf::Vector2f&
     */
    const sf::Vector2f &getPosition() const;

    /**
     * @brief Returns the tile's texture rect.
     *
     * @return sf::IntRect&
     */
    const sf::IntRect &getTextureRect() const;

    /**
     * @brief Returns if the tile is collideable.
     *
     * @return const bool&
     */
    const bool &isCollideable() const;

    /**
     * @brief Returns the tile's collision box shape.
     *
     * @return sf::RectangleShape&
     */
    const sf::RectangleShape &getCollisionBox() const;

    /**
     * @brief Returns the tyle's type
     *
     * @return short (TileTypes enum);
     */
    const TileType &getType() const;

    /**
     * @brief Returns the tile properties as a std::string.
     * @note Returns:
     * @note -> Texture rectangle left
     * @note -> Texture rectangle top
     * @note -> Collision
     * @note -> Collsion box width
     * @note -> Collision box height
     * @note -> Collision box offset x
     * @note -> Collision box offset y
     * @note -> Type
     *
     * @return const TileTypes reference.
     */
    virtual const std::string getPropertiesAsString() const = 0;

    /**
     * @brief Returns the tile collision box global bounds.
     *
     * @return const sf::FloatRect
     */
    const sf::FloatRect getGlobalBounds() const;
};

#endif /* TILE_H_ */
