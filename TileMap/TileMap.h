#ifndef TILEMAP_TILEMAP_H_
#define TILEMAP_TILEMAP_H_

#include "../Tile/Tile.h"

class TileMap
{
private:
	/* VARIABLES */
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u tileMapDimensions;
	std::vector<std::vector<std::vector<Tile*> > > tileMap;

	std::string texture_file_path;

	sf::Texture tileTextureSheet;

	/* PRIVATE FUNCTIONS */
	void clear();
	void resize();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	TileMap(float gridSize, unsigned width, unsigned, std::string texture_file_path);
	virtual ~TileMap();

	/* FUNCTIONS */
	void loadFromFile(const std::string file_name);
	void saveToFile(const std::string file_name);

	void update();
	void render(sf::RenderTarget &target);

	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &textureRect);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);

	/* ACCESSORS */
	const sf::Texture* getTileTextureSheet() const;
};

#endif /* TILEMAP_TILEMAP_H_ */
