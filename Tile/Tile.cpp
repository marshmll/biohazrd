/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "../PCH/stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */
Tile::Tile(float x, float y, float gridSizeF, const sf::Texture &texture, const sf::IntRect textureRect)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tile.setFillColor(sf::Color::White);
	this->tile.setTexture(&texture);
	this->tile.setPosition(x, y);
	this->tile.setTextureRect(textureRect);
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
