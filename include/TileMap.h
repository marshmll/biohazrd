#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	/* VARIABLES */

	float gridSizeF;
	int gridSizeI;
	unsigned layers;

	sf::Vector2i tileMapGridDimensions;
	sf::Vector2f tileMapWorldDimensions;

	std::vector<std::vector<std::vector<std::vector<Tile *>>>> tileMap;

	std::stack<Tile*> deferredTileRendering;

	std::string texture_file_path;
	sf::Texture tileTextureSheet;

	sf::RectangleShape collisionBox;

	int startX;
	int endX;
	int startY;
	int endY;
	int layer;

	/* PRIVATE FUNCTIONS */

	/**
	 * @return void
	 *
	 * @brief Frees all alocated memory for the tiles and texture.
	 */
	void clear();

	/**
	 * @return void
	 *
	 * @brief Resizers the entire map, given the tilemap dimensions.
	 */
	void resize();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */

	/**
	 * @brief This constructor initializes a tilemap.
	 * The constructor also initializes a 3D vector for the x,
	 * y and z coordinates. Also uses a resize vector method to
	 * ensure the vectors are big enough.
	 *
	 * @note The tilemap has some importart properties as:
	 * @note -> Gridsize: the size of each tile, in pixels
	 * @note -> Layers: how many layers each tile position will have
	 * @note -> Dimensions: the size of the tileMap, in tiles
	 */
	TileMap(float gridSize, unsigned grid_width, unsigned grid_height, std::string texture_file_path);

	/**
	 * @brief
	 * Frees all alocated memory for the tiles and texture.
	 */
	virtual ~TileMap();

	/* FUNCTIONS */

	/**
	 * @return void
	 *
	 * @brief Loads a tilemap from a file in the Maps folder.\n
	 * @note Format
	 * @note CONFIG
	 * @note -> Size X and Y.
	 * @note -> Grid size.
	 * @note -> Layers
	 * @note -> Texture file
	 * @note TILES
	 * @note -> Grid position x, y, and layer
	 * @note -> Texture rect x and y
	 * @note -> Collision
	 * @note -> Type.
	 */
	void loadFromFile(const std::string file_name);

	/**
	 * @return void
	 *
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
	 * @note -> Texture rect x and y
	 * @note -> Collision
	 * @note -> Type.
	 */
	void saveToFile(const std::string file_name);

	/**
	 * @return void
	 *
	 * @brief Adds a tile to the tilemap.
	 * X and Y are indexes of the tilemap grid.
	 */

	void addTile(const unsigned x, const unsigned y, const unsigned z,
							 const sf::IntRect &textureRect,
							 const bool &collision, const short &type);

	/**
	 * @return void
	 *
	 * @brief  Removes a tile from the tilemap.
	 * X and Y are indexes of the tilemap grid.
	 */
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update(const float &dt);

	/**
	 * @return void
	 *
	 * @brief Renders each layer of each tile position (x, y).
	 */
	void render(sf::RenderTarget &target, const sf::Vector2i &gridPosition);

	/**
	 * @return void
	 *
	 * @brief Updates the collisions for a entity.
	 */
	void updateCollision(const float &dt, Entity *entity = nullptr);

	/**
	 * @brief Updates the area dimensions around an entity.
	 * 
	 * @return void
	 */
	void updateMapActiveArea(Entity* entity, const int width, const int height);

	/**
	 * @brief Updates the area dimensions with a given grid position.
	 * 
	 * @return void
	 */
	void updateMapActiveArea(const sf::Vector2i gridPosition, const int width, const int height);

	/**
	 * @brief Deferred render for tiles that are suposed to be rendered
	 * later on.
	 * 
	 * @return void
	 */
	void deferredRender(sf::RenderTarget &target);

	/* ACCESSORS */

	/**
	 * @return sf::Texture*
	 *
	 * @brief Returns the tile texture sheet of the tilemap.
	 */
	const sf::Texture *getTileTextureSheet() const;

	/**
	 * @brief Returns how many tiles are in top of the other
	 * in a certain grid position AND layer.
	 * 
	 * @return const unsigned
	 */
	const unsigned getAmountOfStackedTiles(const int x, const int y, const unsigned layer) const;
};

#endif /* TILEMAP_H_ */