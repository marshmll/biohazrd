/*
 * Tile.cpp
 *
 *  Created on: 27 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "Tile.h"

/* CONSTRUCTOR AND DESTRUCTOR */

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,
		   const sf::Texture &texture, const sf::IntRect textureRect,
		   bool collision,
		   short type)
{
	this->tile.setTexture(texture);

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
}

void Tile::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f lightPos)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", lightPos);

		target.draw(this->tile, shader);
	}
	else
	{
		target.draw(this->tile);
	}
}

const bool Tile::intersects(const sf::FloatRect &bounds) const
{
	return this->tile.getGlobalBounds().intersects(bounds);
}

/* ACCESSORS */

const sf::Vector2f &Tile::getPosition() const
{
	return this->tile.getPosition();
}

const bool &Tile::isCollideable() const
{
	return this->collision;
}

const short &Tile::getType() const
{
	return this->type;
}

const std::string Tile::getPropertiesAsString() const
{
	std::stringstream ss;

	ss << this->tile.getTextureRect().left << " " << this->tile.getTextureRect().top << " "
	   << this->collision << " " << this->type;

	return ss.str();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->tile.getGlobalBounds();
}
