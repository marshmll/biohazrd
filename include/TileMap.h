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
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u tileMapGridDimensions;
	sf::Vector2f tileMapWorldDimensions;

	std::vector<std::vector<std::vector<Tile*> > > tileMap;

	std::string texture_file_path;

	sf::Texture tileTextureSheet;

	sf::RectangleShape collisionBox;

	/* PRIVATE FUNCTIONS */
	void clear();
	void resize();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	TileMap(float gridSize, unsigned grid_width, unsigned grid_height, std::string texture_file_path);
	virtual ~TileMap();

	/* FUNCTIONS */
	void loadFromFile(const std::string file_name);
	void saveToFile(const std::string file_name);
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &textureRect,
			const bool &collision, const short &type);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	void update();
	void render(sf::RenderTarget &target, Entity *entity = nullptr);

	void updateCollision(Entity *entity = nullptr);

	/* ACCESSORS */
	const sf::Texture* getTileTextureSheet() const;
};

#endif /* TILEMAP_H_ */
