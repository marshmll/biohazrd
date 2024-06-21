#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "Tiles.h"
#include "Enemies.h"

class Entity;
class Tile;
class Enemy;

class TileMap
{
private:
    /* VARIABLES ====================================================================================== */

    float gridSizeF;
    int gridSizeI;
    unsigned layers;

    sf::Vector2i mapGridDimensions;
    sf::Vector2f mapWorldDimensions;

    std::vector<std::vector<std::vector<std::vector<Tile *>>>> map;

    std::stack<Tile *> deferredTileRendering;

    std::string texture_file_path;
    sf::Texture tileTextureSheet;

    int startX;
    int endX;
    int startY;
    int endY;
    int layer;

    /* PRIVATE FUNCTIONS ====================================================================================== */

    /**
     * @brief Frees all alocated memory for the tiles and texture.
     *
     * @return void
     */
    void clear();

    /**
     * @brief Resizers the entire map, given the tilemap dimensions.
     *
     * @return void
     */
    void resize();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ====================================================================================== */

    /**
     * @brief This constructor initializes a tilemap.
     * The constructor also initializes a 4D vector for the x,
     * y, z and k coordinates. Also uses a resize vector method to
     * ensure the vectors allocate the required amount of memory.
     *
     * @param grid_size The grid size for the tiles.
     * @param map_grid_width The width of the tilemap based on the grid size.
     * @param map_grid_height The height of the tilemap based on the grid size.
     * @param texture_file_path The relative path to the texture sheet.
     */
    TileMap(const float grid_size, const unsigned map_grid_width, const unsigned map_grid_height,
            const std::string texture_file_path);

    /**
     * @brief This constructor initializes a tilemap.
     * The constructor also initializes a 4D vector for the x,
     * y, z and k coordinates. Also uses a resize vector method to
     * ensure the vectors allocate the required amount of memory.
     *
     * @param map_file_path The relative path to a map file.
     */
    TileMap(const std::string map_file_path);

    /**
     * @brief
     * Frees all alocated memory for the tiles and texture.
     */
    virtual ~TileMap();

    /* FUNCTIONS ====================================================================================== */

    /**
     * @brief Loads a tilemap from a file in the Maps folder.\n
     * @note Format
     * @note CONFIG
     * @note -> Size X and Y.
     * @note -> Grid size.
     * @note -> Layers
     * @note -> Texture file
     *
     * @note TILES
     * @note -> Grid position x, y, and layer
     * @note -> Type
     * @note -> Tile type's specific data.
     *
     * @return void
     */
    void loadFromFile(const std::string file_path);

    /**
     * @brief Saves the tilemap to a file in the Maps folder.
     * @note Format
     * @note CONFIG
     * @note -> Size X and Y.
     * @note -> Grid size.
     * @note -> Layers
     * @note -> Texture file
     *
     * @note TILES
     * @note -> Grid position x, y, and layer
     * @note -> Type
     * @note -> Tile type's specific data.
     *
     * @return void
     */
    void saveToFile(const std::string file_path);

    /**
     * @brief Adds a tile to the tilemap.
     * @param x The x coordinate relative to world grid.
     * @param y The y coordinate relative to world grid.
     * @param texture_rect The tile's texture rect reference.
     * @param collision A flag for enabling collision
     * @param coll_box_width The tile's collision box width
     * @param coll_box_height The tile's collision box height
     * @param coll_box_offset_x The tile's collision box offset x.
     * @param coll_box_offset_y The tile's collision box offset y.
     * @param type The tile's type.
     *
     * @return void
     */
    void addTile(
        const unsigned x, const unsigned y, const unsigned z,
        const sf::IntRect &texture_rect,
        const bool &collision,
        const float coll_box_width, const float coll_box_height,
        const float coll_box_offset_x, const float coll_box_offset_y,
        const TileType &type);

    /**
     * @brief Adds a spawner in the map.
     * @param x The x coordinate relative to world grid.
     * @param y The y coordinate relative to world grid.
     * @param texture_rect The tile's texture rect reference.
     * @param enemy_type The spawner's enemy type.
     * @param enemy_amount The spawner's enemy amount.
     * @param enemy_time_to_spawn The spawner's time to spawn an enemy.
     * @param enemy_max_distance The max distance that the enemies can get away from the spawner.
     *
     * @return void
     */
    void addSpawner(
        const unsigned x, const unsigned y, const unsigned z,
        const sf::IntRect &texture_rect,
        const int enemy_type, const int enemy_amount,
        const int enemy_time_to_spawn, const int enemy_max_distance);

    /**
     * @brief  Removes a tile from the tilemap.
     * @param x The x coordinate relative to the world grid.
     * @param y The y coordinate relative to the world grid.
     * @param layer The layer of the tile.
     *
     * @return void
     */
    void removeTile(const unsigned x, const unsigned y, const unsigned layer);

    /**
     * @brief Updates the entire tilemap.
     *
     * @param dt The game delta time.
     * @param entity A pointer to an entity.
     *
     * @return void
     */
    void update(const float &dt, Entity *entity);

    /**
     * @brief Renders all the tiles in the tilemap.
     * @note Renders each x, y, z and k tiles.
     * @note If a shader is passed in, it will be used for
     * rendering the tiles.
     *
     * @param target A render target for rendering the tiles.
     * @param gridPosition A culling area for rendering
     * @param show_collision_box A flag for rendering the collision boxes (default: false)
     * @param shader A pointer to a shader. (default: nullptr)
     * @param player_positon A sf::Vector2f for the player's center position (default sf::Vector2f()).
     *
     * @return void
     */
    void render(
        sf::RenderTarget &target, const sf::Vector2i &grid_position, sf::VideoMode &vm,
        const bool show_collision_box = false, const bool use_deferred_render = false,
        sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    /**
     * @brief Renders tiles that had its rendering delayed. Renders and
     * pops the deferred tile from the deffered render stack.
     *
     * @param target A target to render in.
     * @param shader A shader to use. (default = nullptr)
     * @param light_pos The light position. (default = sf::Vector2f())
     *
     * @return void
     */
    void deferredRender(
        sf::RenderTarget &target, sf::Shader *shader = nullptr,
        const sf::Vector2f light_pos = sf::Vector2f());

    /**
     * @brief Updates the entity collision with the world bounds.
     * @param dt The game delta time.
     * @param entity A pointer to an entity.
     *
     * @note -> Updates only the map active area specified in this->updateMapActiveArea.
     *
     * @return void
     */
    void updateWorldBoundsCollision(const float &dt, Entity *entity);

    /**
     * @brief Updates the entity collision with the map tiles.
     * @param dt The game delta time.
     * @param entity A pointer to an entity.
     *
     * @note -> Updates only the map active area specified in this->updateMapActiveArea.
     *
     * @return void
     */
    void updateTileCollision(const float &dt, Entity *entity);

    /**
     * @brief Updates the map tiles.
     * @param dt The game delta time.
     * @param entity A pointer to an entity.
     * @param enemies A reference to the enemies vector
     * @param textures A reference to the textures map.
     *
     * @note -> Updates only the map active area specified in this->updateMapActiveArea.
     *
     * @return void
     */
    void updateTiles(const float &dt, Entity *entity,
                     std::vector<Enemy *> &enemies, std::map<std::string, sf::Texture> &textures);

    /**
     * @return void
     *
     * @brief Updates the area dimensions around an entity.
     */
    void updateMapActiveArea(Entity *entity, const int width, const int height);

    /**
     * @brief Updates the area dimensions with a given grid position.
     *
     * @return void
     */
    void updateMapActiveArea(const sf::Vector2i grid_position, const int width, const int height);

    /* ACCESSORS ====================================================================================== */

    /**
     * @brief Checks if a tile in a x, y and z coordinate are from a given type.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param layer The layer.
     * @param type The type to check.
     * @note -> Use the TileTypes enum.
     * @note -> Returns false if outside world bounds or empty tile.
     *
     * @return const bool
     */
    const bool compareType(const int x, const int y, const unsigned layer, const TileType &type) const;

    /**
     * @brief Returns the tilemap's size.
     *
     * @return sf::Vector2f
     */
    const sf::Vector2f &getSize() const;

    /**
     * @brief Returns the tile texture sheet of the tilemap.
     *
     * @return sf::Texture*
     */
    const sf::Texture *getTileTextureSheet() const;

    /**
     * @brief Returns how many tiles are in top of the other
     * in a certain grid position AND layer.
     * @note -> Returns -1 if the position is out of bounds.
     *
     * @return const int
     */
    const int getAmountOfStackedTiles(const int x, const int y, const unsigned layer) const;

    /**
     * @brief Checks if a tile in a x, y and z coordinate are from a given type.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @param layer The layer.
     * @note -> Returns true if outside world bounds.
     *
     * @return const bool
     */
    const bool isTileEmpty(const int x, const int y, const unsigned layer) const;
};

#endif /* TILEMAP_H_ */