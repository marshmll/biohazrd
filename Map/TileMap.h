#ifndef MAP_TILEMAP_H_
#define MAP_TILEMAP_H_

#include "../Tile/Tile.h"

class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile> > > map;

public:
	TileMap();
	virtual ~TileMap();

	/* FUNCTIONS */
	void update();
	void render(sf::RenderTarget &target);
};

#endif /* MAP_TILEMAP_H_ */
