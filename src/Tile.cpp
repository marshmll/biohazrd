/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */
Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture &texture, const sf::IntRect textureRect,
		bool collision,
		short type)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));

	this->tile.setFillColor(sf::Color::White);

	this->tile.setTexture(&texture);

	this->tile.setPosition(grid_x * gridSizeF, grid_y * gridSizeF);

	this->tile.setTextureRect(textureRect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}

/* FUNCTIONS */
void Tile::update()
{
	/**
	 * @return void
	 */
}

void Tile::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders the tile into a target.
	 */

	target.draw(this->tile);
}

/* ACCESSORS */
const sf::Vector2f& Tile::getPosition() const
{
	/**
	 * @return const sf::Vector2f&
	 *
	 * Returns the tile's current position.
	 */

	return this->tile.getPosition();
}

const bool& Tile::isCollideable()
{
	/**
	 * @return const bool&
	 *
	 * Returns if the tile is collideable.
	 */

	return this->collision;
}

const std::string Tile::getPropertiesAsString() const
{
	/**
	 * @return void
	 *
	 * Returns the tile properties as a std::string.
	 */

	std::stringstream ss;

	ss << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " "
			<< this->collision << " " << this->type;

	return ss.str();
}
