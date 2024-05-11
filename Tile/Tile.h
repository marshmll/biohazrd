#ifndef TILE_TILE_H_
#define TILE_TILE_H_

enum TileTypes
{
	DEFAULT = 0,
	HARMFUL
};

class Tile
{
private:

protected:
	sf::RectangleShape tile;

	bool collision;
	short type;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture &texture, const sf::IntRect textureRect,
			bool collision = false, short type = TileTypes::HARMFUL);
	virtual ~Tile();

	/* FUNCTIONS */
	void update();
	void render(sf::RenderTarget &target);

	/* ACCESSORS */
	const sf::Vector2f& getPosition() const;
	const bool& isCollideable();
	const std::string getPropertiesAsString() const;
};

#endif /* TILE_TILE_H_ */
