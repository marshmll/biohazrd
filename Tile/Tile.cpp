/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "../PCH/stdafx.h"
#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF)
{
	this->tile.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tile.setFillColor(sf::Color::Green);
	this->tile.setPosition(x, y);
}

Tile::~Tile()
{

}

/* FUNCTIONS */
void Tile::update()
{

}

void Tile::render(sf::RenderTarget &target)
{
	target.draw(this->tile);
}
