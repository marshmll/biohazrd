#ifndef TILE_H_
#define TILE_H_

enum TileTypes
{
	DEFAULT = 0,
	HARMFUL,
	DOODAD
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
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,
		 const sf::Texture &texture, const sf::IntRect textureRect,
		 bool collision = false, short type = TileTypes::DEFAULT);

	virtual ~Tile();

	/* FUNCTIONS */

	/**
	 * @brief Updates the tile.
	 *
	 * @return void
	 */
	void update();

	/**
	 * @brief Renders the tile into a target.
	 *
	 * @return void
	 */
	void render(sf::RenderTarget &target);

	/**
	 * @brief Returns if the tile intersects a given
	 * FloatRect.
	 *
	 * @return bool
	 */
	const bool intersects(const sf::FloatRect &bounds) const;

	/* ACCESSORS */

	/**
	 * @brief Returns the tile's current position.
	 *
	 * @return const sf::Vector2f&
	 */
	const sf::Vector2f &getPosition() const;

	/**
	 * @brief Returns if the tile is collideable.
	 *
	 * @return const bool&
	 */
	const bool &isCollideable() const;

	/**
	 * @brief Returns the tyle's type
	 *
	 * @return short (TileTypes enum);
	 */
	const short &getType() const;

	/**
	 * @brief Returns the tile properties as a std::string.
	 * @note Returns:
	 * @note -> Texture rectangle left
	 * @note -> Texture rectangle top
	 * @note -> Collision
	 * @note -> Type
	 *
	 * @return void
	 */
	const std::string getPropertiesAsString() const;

	/**
	 * @brief Returns the tile's global bounds.
	 *
	 * @return const sf::FloatRect
	 */
	const sf::FloatRect getGlobalBounds() const;
};

#endif /* TILE_H_ */
