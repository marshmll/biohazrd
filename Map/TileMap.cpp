/*
 * TileMap.cpp
 *
 *  Created on: 30 de abr. de 2024
 *      Author: renan
 */

#include "../PCH/stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = (unsigned) this->gridSizeF;
	this->layers = 1;

	this->maxSize.x = 10;
	this->maxSize.y = 10;

	this->map.reserve(this->maxSize.x);

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector<std::vector<Tile>>());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].reserve(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].reserve(this->layers);
				this->map[x][y].push_back(Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{

}

/* FUNCTIONS */
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				z.render(target);
			}
		}
	}
}

