/*
 * TileMap.cpp
 *
 *  Created on: 30 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "TileMap.h"

/* PRIVATE FUNCTIONS */

void TileMap::clear()
{
    for (auto &x : this->tileMap)
    {
        for (auto &y : x)
        {
            for (auto &z : y)
            {
                for (auto k : z)
                {
                    delete k;
                    k = nullptr;
                }
                z.clear();
            }
            y.clear();
        }
        x.clear();
    }

    this->tileMap.clear();
}

void TileMap::resize()
{
    this->tileMap.resize(this->tileMapGridDimensions.x, std::vector<std::vector<std::vector<Tile *>>>());
    for (size_t x = 0; x < this->tileMapGridDimensions.x; x++)
    {
        for (size_t y = 0; y < this->tileMapGridDimensions.y; y++)
        {
            this->tileMap[x].resize(this->tileMapGridDimensions.y, std::vector<std::vector<Tile *>>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->tileMap[x][y].resize(this->layers, std::vector<Tile *>());
            }
        }
    }
}

/* CONSTRUCTOR AND DESTRUCTOR */

TileMap::TileMap(const float grid_size, const unsigned grid_width, const unsigned grid_height,
                 const std::string texture_file_path)
{
    this->gridSizeF = grid_size;
    this->gridSizeI = (int)this->gridSizeF;
    this->layers = 1;

    this->tileMapGridDimensions.x = grid_width;
    this->tileMapGridDimensions.y = grid_height;

    this->tileMapWorldDimensions.x = grid_width * grid_size;
    this->tileMapWorldDimensions.y = grid_height * grid_size;

    this->resize();

    this->texture_file_path = texture_file_path;

    if (!this->tileTextureSheet.loadFromFile(texture_file_path))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

    this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineColor(sf::Color(255, 0, 0, 100));
    this->collisionBox.setOutlineThickness(1.f);

    this->startX = 0;
    this->endX = 0;
    this->startY = 0;
    this->endY = 0;
    this->layer = 0;
}

TileMap::TileMap(const std::string map_file_path)
{
    this->loadFromFile(map_file_path);
}

TileMap::~TileMap()
{
    this->clear();
}

/* FUNCTIONS */

void TileMap::loadFromFile(const std::string file_path)
{
    std::ifstream in_file;

    // Try to open a file.
    in_file.open(file_path);

    // If couldn'd open file, runtime error.
    if (!in_file.is_open())
        ErrorHandler::throwErr("TILEMAP::LOADFROMFILE::ERR_COULD_NOT_LOAD_TILEMAP_FROM_FILE\n");

    // Data to be loaded in
    unsigned grid_width = 0;
    unsigned grid_height = 0;
    int grid_size = 0;

    unsigned layers = 0;

    std::string texture_file_path;

    int grid_x = 0;
    int grid_y = 0;
    unsigned z = 0;
    unsigned k = 0;

    unsigned txtrRectX;
    unsigned txtrRectY;

    bool collision = false;
    short type = TileTypes::DEFAULT;

    // Load CONFIG
    in_file >> grid_width >> grid_height >> grid_size >> layers >> texture_file_path;

    this->gridSizeF = (float)grid_size;
    this->gridSizeI = grid_size;
    this->layers = layers;

    this->tileMapGridDimensions.x = grid_width;
    this->tileMapGridDimensions.y = grid_height;

    this->tileMapWorldDimensions.x = static_cast<float>(grid_width) * gridSizeF;
    this->tileMapWorldDimensions.y = static_cast<float>(grid_height) * gridSizeF;

    this->texture_file_path = texture_file_path;

    // If failed to load texture
    if (!this->tileTextureSheet.loadFromFile(texture_file_path))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

    this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineColor(sf::Color(255, 0, 0, 100));
    this->collisionBox.setOutlineThickness(1.f);

    this->startX = 0;
    this->endX = 0;
    this->startY = 0;
    this->endY = 0;
    this->layer = 0;

    // Clear the map
    this->clear();

    // Resize the map
    this->resize();

    // While not in the end of file
    while (in_file >> grid_x >> grid_y >> z >> k >> txtrRectX >> txtrRectY >> collision >> type)
    {
        this->tileMap[grid_x][grid_y][z].insert(
            this->tileMap[grid_x][grid_y][z].begin() + k,
            new Tile(
                grid_x, grid_y, this->gridSizeF, this->tileTextureSheet,
                sf::IntRect(txtrRectX, txtrRectY, this->gridSizeI, this->gridSizeI),
                collision, type));
    }

    in_file.close();
}

void TileMap::saveToFile(const std::string file_path)
{
    std::ofstream out_file;

    // Try to open a file.
    out_file.open(file_path);

    // If couldn'd open file, throw runtime error.
    if (!out_file.is_open())
        ErrorHandler::throwErr("TILEMAP::SAVETOFILE::ERR_COULD_NOT_SAVE_TILEMAP_TO_FILE\n");

    out_file << this->tileMapGridDimensions.x << " " << this->tileMapGridDimensions.y << "\n"
             << this->gridSizeI << "\n"
             << this->layers << "\n"
             << this->texture_file_path << "\n";

    // Write all tiles information
    for (size_t x = 0; x < this->tileMapGridDimensions.x; x++)
    {
        for (size_t y = 0; y < this->tileMapGridDimensions.y; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                if (!this->tileMap[x][y][z].empty())
                {
                    for (size_t k = 0; k < this->tileMap[x][y][z].size(); k++)
                    {
                        out_file << x << " " << y << " " << z << " " << k << " "
                                 << this->tileMap[x][y][z][k]->getPropertiesAsString()
                                 << "\n";
                    }
                }
            }
        }
    }

    out_file.close();
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z,
                      const sf::IntRect &textureRect,
                      const bool &collision, const short &type)
{
    // If position is in the map bounds
    if (x < this->tileMapGridDimensions.x && y < this->tileMapGridDimensions.y && z < this->layers)
    {
        if (!this->tileMap[x][y][z].empty())
        {
            // If the texture of the tile to be placed is not equal to
            // the texture of the tile already on the vector
            if (this->tileMap[x][y][z].back()->getTextureRect() != textureRect)
            {
                this->tileMap[x][y][z].push_back(new Tile(
                    x, y, this->gridSizeF, this->tileTextureSheet,
                    textureRect, collision, type));
            }
        }
        else
        {
            this->tileMap[x][y][z].push_back(new Tile(
                x, y, this->gridSizeF, this->tileTextureSheet,
                textureRect, collision, type));
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
    // If position is in the map bounds
    if (x < this->tileMapGridDimensions.x && y < this->tileMapGridDimensions.y && z < this->layers)
    {
        // If the place to remove is not empty
        if (!this->tileMap[x][y][z].empty())
        {
            delete this->tileMap[x][y][z].back();
            this->tileMap[x][y][z].pop_back();
        }
    }
}

void TileMap::update(const float &dt, Entity *entity)
{
    /* WORLD BOUNDS */

    // X axis
    if (entity->getPosition().x < 0.f)
    {
        entity->setPosition(sf::Vector2f(0.f, entity->getPosition().y));
        entity->stopVelocityX();
    }
    else if (entity->getPosition().x + entity->getSize().x > this->tileMapWorldDimensions.x)
    {
        entity->stopVelocityX();
        entity->setPosition(
            sf::Vector2f(this->tileMapWorldDimensions.x - entity->getSize().x, entity->getPosition().y));
    }

    // Y axis
    if (entity->getPosition().y < 0.f)
    {
        entity->stopVelocityY();
        entity->setPosition(sf::Vector2f(entity->getPosition().x, 0.f));
    }
    else if (entity->getPosition().y + entity->getSize().y > this->tileMapWorldDimensions.y)
    {
        entity->stopVelocityY();
        entity->setPosition(
            sf::Vector2f(entity->getPosition().x, this->tileMapWorldDimensions.y - entity->getSize().y));
    }

    /* TILES */

    this->updateMapActiveArea(entity, 5, 5);

    for (size_t x = this->startX; x < this->endX; x++)
    {
        for (size_t y = this->startY; y < this->endY; y++)
        {
            for (size_t k = 0; k < this->tileMap[x][y][this->layer].size(); k++)
            {
                this->tileMap[x][y][this->layer][k]->update();

                if (this->tileMap[x][y][this->layer][k]->isCollideable())
                {
                    sf::FloatRect playerBounds = entity->getGlobalBounds();
                    sf::FloatRect wallBounds = this->tileMap[x][y][this->layer][k]->getGlobalBounds();
                    sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

                    if (nextPositionBounds.intersects(wallBounds))
                    {
                        if (entity->getDirection() == "UP")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + dt * (entity->getMaxVelocity() / 10.f)));
                        }
                        if (entity->getDirection() == "DOWN")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - dt * (entity->getMaxVelocity() / 10.f)));
                        }
                        if (entity->getDirection() == "LEFT")
                        {
                            entity->stopVelocityX();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x + dt * (entity->getMaxVelocity() / 10.f), entity->getPosition().y));
                        }
                        if (entity->getDirection() == "RIGHT")
                        {
                            entity->stopVelocityX();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x - dt * (entity->getMaxVelocity() / 10.f), entity->getPosition().y));
                        }
                    }
                }
            }
        }
    }
}

void TileMap::render(
    sf::RenderTarget &target, const sf::Vector2i &grid_position, sf::VideoMode &vm,
    const bool show_collision_box, const bool use_deferred_render, sf::Shader *shader,
    const sf::Vector2f player_position)
{
    int active_area_width = static_cast<int>(std::ceil(static_cast<float>(vm.width) / this->gridSizeF)) + 2;
    int active_area_height = static_cast<int>(std::ceil(static_cast<float>(vm.height) / this->gridSizeF) + 2);

    this->updateMapActiveArea(grid_position, active_area_width, active_area_height);

    for (size_t x = this->startX; x < this->endX; x++)
    {
        for (size_t y = this->startY; y < this->endY; y++)
        {
            for (size_t k = 0; k < this->tileMap[x][y][this->layer].size(); k++)
            {
                if (this->tileMap[x][y][this->layer][k]->getType() == TileTypes::DOODAD && use_deferred_render)
                {
                    this->deferredTileRendering.push(this->tileMap[x][y][this->layer][k]);
                }
                else
                {
                    if (shader)
                        this->tileMap[x][y][this->layer][k]->render(target, shader, player_position);
                    else
                        this->tileMap[x][y][this->layer][k]->render(target);
                }

                if (show_collision_box)
                {
                    if (this->tileMap[x][y][this->layer][k]->isCollideable())
                    {
                        this->collisionBox.setPosition(this->tileMap[x][y][this->layer][k]->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
            }
        }
    }
}

void TileMap::deferredRender(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f player_position)
{
    while (!this->deferredTileRendering.empty())
    {
        if (shader)
            this->deferredTileRendering.top()->render(target, shader, player_position);
        else
            this->deferredTileRendering.top()->render(target);

        this->deferredTileRendering.pop();
    }
}

void TileMap::updateMapActiveArea(Entity *entity, const int width, const int height)
{
    this->layer = 0;

    this->startX = entity->getGridPosition(this->gridSizeI).x - width / 2;
    if (this->startX < 0)
        this->startX = 0;
    else if (this->startX >= this->tileMapGridDimensions.x)
        this->startX = this->tileMapGridDimensions.x;

    this->endX = entity->getGridPosition(this->gridSizeI).x + (width / 2) + 1;
    if (this->endX < 0)
        this->endX = 0;
    else if (this->endX >= this->tileMapGridDimensions.x)
        this->endX = this->tileMapGridDimensions.x;

    this->startY = entity->getGridPosition(this->gridSizeI).y - height / 2;
    if (this->startY < 0)
        this->startY = 0;
    else if (this->startY >= this->tileMapGridDimensions.x)
        this->startY = this->tileMapGridDimensions.y;

    this->endY = entity->getGridPosition(this->gridSizeI).y + (height / 2) + 1;
    if (this->endY < 0)
        this->endY = 0;
    else if (this->endY >= this->tileMapGridDimensions.y)
        this->endY = this->tileMapGridDimensions.y;
}

void TileMap::updateMapActiveArea(const sf::Vector2i gridPosition, const int width, const int height)
{
    this->layer = 0;

    this->startX = gridPosition.x - width / 2;
    if (this->startX < 0)
        this->startX = 0;
    else if (this->startX >= this->tileMapGridDimensions.x)
        this->startX = this->tileMapGridDimensions.x;

    this->endX = gridPosition.x + width / 2 + 1;
    if (this->endX < 0)
        this->endX = 0;
    else if (this->endX >= this->tileMapGridDimensions.x)
        this->endX = this->tileMapGridDimensions.x;

    this->startY = gridPosition.y - height / 2;
    if (this->startY < 0)
        this->startY = 0;
    else if (this->startY >= this->tileMapGridDimensions.x)
        this->startY = this->tileMapGridDimensions.y;

    this->endY = gridPosition.y + height / 2 + 1;
    if (this->endY < 0)
        this->endY = 0;
    else if (this->endY >= this->tileMapGridDimensions.y)
        this->endY = this->tileMapGridDimensions.y;
}

/* ACCESSORS */

const sf::Vector2f &TileMap::getSize() const
{
    return this->tileMapWorldDimensions;
}

const sf::Texture *TileMap::getTileTextureSheet() const
{
    return &this->tileTextureSheet;
}

const int TileMap::getAmountOfStackedTiles(const int x, const int y, const unsigned layer) const
{
    if (x >= 0 && y >= 0 && x < this->tileMap.size())
    {
        if (y < this->tileMap[x].size())
        {
            if (layer >= 0 && layer < this->tileMap[x][y].size())
            {
                return static_cast<int>(this->tileMap[x][y][layer].size());
            }
        }
    }

    return -1;
}
