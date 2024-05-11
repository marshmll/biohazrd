/*
 * TileMap.cpp
 *
 *  Created on: 30 de abr. de 2024
 *      Author: renan
 */

#include "../PCH/stdafx.h"
#include "TileMap.h"

/* PRIVATE FUNCTIONS */
void TileMap::clear()
{
	/**
	 * @return void
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
				z = nullptr;
			}
			y.clear();
		}
		x.clear();
	}

	this->tileMap.clear();
}

void TileMap::resize()
{
	/**
	 * @return void
	 *
	 * Resizers the entire map, given the tilemap dimensions.
	 */

	this->tileMap.resize(this->tileMapGridDimensions.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->tileMapGridDimensions.x; x++)
	{
		for (size_t y = 0; y < this->tileMapGridDimensions.y; y++)
		{
			this->tileMap[x].resize(this->tileMapGridDimensions.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->tileMap[x][y].resize(this->layers, nullptr);
			}
		}
	}
}

/* CONSTRUCTOR AND DESTRUCTOR */
TileMap::TileMap(float gridSize, unsigned grid_width, unsigned grid_height, std::string texture_file_path)
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

	this->tileMapGridDimensions.x = grid_width;
	this->tileMapGridDimensions.y = grid_height;

	this->tileMapWorldDimensions.x = grid_width * gridSize;
	this->tileMapWorldDimensions.y = grid_height * gridSize;

	this->resize();

	this->texture_file_path = texture_file_path;

	if (!this->tileTextureSheet.loadFromFile(texture_file_path))
		throw std::runtime_error("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE: " + texture_file_path);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color(255, 0, 0, 100));
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	/**
	 * @destructor
	 *
	 * Frees all alocated memory for the tiles and texture.
	 */

	this->clear();
}

/* FUNCTIONS */
void TileMap::loadFromFile(const std::string file_name)
{
	/**
	 * @return void
	 *
	 * Loads a tilemap from a file in the Maps folder.
	 *
	 * Format
	 * CONFIG
	 * -> Size X and Y.
	 * -> Grid size.
	 * -> Layers
	 * -> Texture file
	 *
	 * TILES
	 * -> Grid position x, y, and layer
	 * -> Texture rect x and y
	 * -> Collision
	 * -> Type.
	 */

	std::ifstream in_file;

	// Try to open a file.
	in_file.open("Maps/" + file_name);

	// If couldn'd open file, throw runtime error.
	if (!in_file.is_open())
		throw std::runtime_error("TILEMAP::LOADFROMFILE::ERR_COULD_NOT_LOAD_TILEMAP_FROM_FILE: " + file_name);

	// Data to be loaded in
	sf::Vector2u size;
	unsigned gridSize = 0;

	unsigned layers = 0;

	std::string texture_file_path;

	unsigned grid_x = 0;
	unsigned grid_y = 0;
	unsigned z = 0;

	unsigned txtrRectX;
	unsigned txtrRectY;

	bool collision = false;
	short type = TileTypes::DEFAULT;

	// Load CONFIG
	in_file >> size.x >> size.y >> gridSize >> layers >> texture_file_path;

	this->tileMapGridDimensions.x = size.x;
	this->tileMapGridDimensions.y = size.y;

	this->gridSizeF = (float) gridSize;
	this->gridSizeU = gridSize;
	this->layers = layers;

	// Clear the map
	this->clear();

	// Resize the map
	this->resize();

	this->texture_file_path = texture_file_path;

	// If failed to load texture
	if (!this->tileTextureSheet.loadFromFile(texture_file_path))
		throw std::runtime_error("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE: " + texture_file_path);

	// While not in the end of file
	while (in_file >> grid_x >> grid_y >> z >> txtrRectX >> txtrRectY >> collision >> type)
	{
		this->tileMap[grid_x][grid_y][z] = new Tile(
				grid_x, grid_y,
				this->gridSizeF,
				this->tileTextureSheet,
				sf::IntRect(txtrRectX, txtrRectY, this->gridSizeU, this->gridSizeU),
				collision,
				type);
	}

	in_file.close();

}

void TileMap::saveToFile(const std::string file_name)
{
	/**
	 * @return void
	 *
	 * Saves the tilemap to a file in the Maps folder.
	 *
	 * Format
	 * CONFIG
	 * -> Size X and Y.
	 * -> Grid size.
	 * -> Layers
	 * -> Texture file
	 *
	 * TILES
	 * -> Grid position x, y, and layer
	 * -> Texture rect x and y
	 * -> Collision
	 * -> Type.
	 */

	std::ofstream out_file;

	// Try to open a file.
	out_file.open("Maps/" + file_name);

	// If couldn'd open file, throw runtime error.
	if (!out_file.is_open())
		throw std::runtime_error("TILEMAP::SAVETOFILE::ERR_COULD_NOT_SAVE_TILEMAP_TO_FILE: " + file_name);

	out_file << this->tileMapGridDimensions.x << " " << this->tileMapGridDimensions.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->texture_file_path << "\n";

	// Write all tiles information
	for (size_t x = 0; x < this->tileMapGridDimensions.x; x++)
	{
		for (size_t y = 0; y < this->tileMapGridDimensions.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				if (this->tileMap[x][y][z] != nullptr)
					out_file << x << " " << y << " " << z << " " << this->tileMap[x][y][z]->getPropertiesAsString()
							<< "\n";
			}
		}
	}

	out_file.close();
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &textureRect,
		const bool &collision, const short &type)
{
	/**
	 * @return void
	 *
	 * Adds a tile to the tilemap.
	 * X and Y are indexes of the tilemap grid.
	 */

	// If position is in the map bounds
	if (x < this->tileMapGridDimensions.x && y < this->tileMapGridDimensions.y && z < this->layers)
	{
		this->tileMap[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileTextureSheet, textureRect, collision, type);
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
	if (x < this->tileMapGridDimensions.x && y < this->tileMapGridDimensions.y && z < this->layers)
	{
		// If the place to remove is not empty
		if (this->tileMap[x][y][z] != nullptr)
		{
			delete this->tileMap[x][y][z];
			this->tileMap[x][y][z] = nullptr;
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget &target, Entity *Entity)
{
	/**
	 * @return void
	 *
	 * Renders each layer of each tile position (x, y).
	 */

	for (auto &x : this->tileMap)
	{
		for (auto &y : x)
		{
			for (auto *z : y)
			{
				if (z != nullptr)
				{
					z->render(target);

					// COLLISION DEBUG
					if (z->isCollideable())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}

void TileMap::updateCollision(Entity *entity)
{
	/**
	 * @return void
	 *
	 * Updates the collisions for a entity.
	 */

	/* WORLD BOUNDS */

	// X axis
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(sf::Vector2f(0.f, entity->getPosition().y));
	}
	else if (entity->getPosition().x + entity->getSize().x > this->tileMapWorldDimensions.x)
	{
		entity->setPosition(
				sf::Vector2f(this->tileMapWorldDimensions.x - entity->getSize().x, entity->getPosition().y));
	}

	// Y axis
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(sf::Vector2f(entity->getPosition().x, 0.f));
	}
	else if (entity->getPosition().y + entity->getSize().y > this->tileMapWorldDimensions.y)
	{
		entity->setPosition(
				sf::Vector2f(entity->getPosition().x, this->tileMapWorldDimensions.y - entity->getSize().y));
	}
}

/* ACCESSORS */
const sf::Texture* TileMap::getTileTextureSheet() const
{
	/**
	 * @return sf::Texture*
	 *
	 * Returns the tile texture sheet of the tilemap.
	 */

	return &this->tileTextureSheet;
}
