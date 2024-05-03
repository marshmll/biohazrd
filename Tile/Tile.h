#ifndef TILE_TILE_H_
#define TILE_TILE_H_

class Tile
{
private:

protected:
	sf::RectangleShape tile;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect textureRect);
	virtual ~Tile();

	/* FUNCTIONS */
	void update();
	void render(sf::RenderTarget &target);
};

#endif /* TILE_TILE_H_ */
