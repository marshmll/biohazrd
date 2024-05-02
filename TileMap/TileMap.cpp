/*
 * TileMap.cpp
 *
 *  Created on: 30 de abr. de 2024
 *      Author: renan
 */

#include "../PCH/stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	/**
	 * @constructor
	 *
	 * This constructor initializes a tilemap.
	 * The tilemap has some importart properties as:
	 * -> Gridsize: the size of each tile, in pixels
	 * -> Layers: how many layers each tile position will have
	 * -> Dimensions: the size of the tileMap, in tiles
	 *
	 * The constructor also initializes a 3D vector for the x,
	 * y and z coordinates. Also uses a resize vector method to
	 * ensure the vectors are big enough.
	 */

	this->gridSizeF = gridSize;
	this->gridSizeU = (unsigned) this->gridSizeF;
	this->layers = 1;

	this->tileMapDimensions.x = width;
	this->tileMapDimensions.y = height;

	this->tileMap.resize(this->tileMapDimensions.x, std::vector<std::vector<Tile*>>());

	for (size_t x = 0; x < this->tileMapDimensions.x; x++)
	{
		for (size_t y = 0; y < this->tileMapDimensions.y; y++)
		{
			this->tileMap[x].resize(this->tileMapDimensions.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->tileMap[x][y].resize(this->layers, nullptr);
			}
		}
	}

	if (!this->tileTextureSheet.loadFromFile("Assets/Images/Tiles/grass.png"))
		throw std::runtime_error("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES");
}

TileMap::~TileMap()
{
	/**
	 * @destructor
	 *
	 * Frees all alocated memory for the tiles and texture.
	 */

	for (auto &x : this->tileMap)
	{
		for (auto &y : x)
		{
			for (auto &z : y)
			{
				delete z;
			}
		}
	}
}

/* FUNCTIONS */
void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target)
{
	/**
	 * @return void
	 *
	 * Renders each layer of each tile position (X, y).
	 */

	for (auto &x : this->tileMap)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if (z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	/**
	 * @return void
	 *
	 * Adds a tile to the tilemap.
	 * X and Y are indexes of the tilemap grid.
	 */

	// If position is in the map bounds
	if (x < this->tileMapDimensions.x && y < this->tileMapDimensions.y && z < this->layers)
	{
		// If the place to add is empty
		if (this->tileMap[x][y][z] == nullptr)
		{
			this->tileMap[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/**
	 * @return void
	 *
	 * Removes a tile from the tilemap.
	 * X and Y are indexes of the tilemap grid.
	 */

	// If position is in the map bounds
	if (x < this->tileMapDimensions.x && y < this->tileMapDimensions.y && z < this->layers)
	{
		// If the place to remove is not empty
		if (this->tileMap[x][y][z] != nullptr)
		{
			delete this->tileMap[x][y][z];
			this->tileMap[x][y][z] = nullptr;
		}
	}
}

