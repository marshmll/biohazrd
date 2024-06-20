/*
 * TileMap.cpp
 *
 *  Created on: 30 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "TileMap.h"

/* PRIVATE FUNCTIONS =========================================================================================== */

void TileMap::clear()
{
    for (auto &x : this->map)
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

    this->map.clear();
}

void TileMap::resize()
{
    this->map.resize(this->mapGridDimensions.x, std::vector<std::vector<std::vector<Tile *>>>());
    for (size_t x = 0; x < this->mapGridDimensions.x; x++)
    {
        for (size_t y = 0; y < this->mapGridDimensions.y; y++)
        {
            this->map[x].resize(this->mapGridDimensions.y, std::vector<std::vector<Tile *>>());

            for (size_t z = 0; z < this->layers; z++)
            {
                this->map[x][y].resize(this->layers, std::vector<Tile *>());
            }
        }
    }
}

/* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

TileMap::TileMap(const float grid_size, const unsigned map_grid_width, const unsigned map_grid_height,
                 const std::string texture_file_path)
{
    this->gridSizeF = grid_size;
    this->gridSizeI = (int)this->gridSizeF;
    this->layers = 1;

    this->mapGridDimensions.x = map_grid_width;
    this->mapGridDimensions.y = map_grid_height;

    this->mapWorldDimensions.x = map_grid_width * grid_size;
    this->mapWorldDimensions.y = map_grid_height * grid_size;

    this->resize();

    this->texture_file_path = texture_file_path;

    if (!this->tileTextureSheet.loadFromFile(texture_file_path))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

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

/* FUNCTIONS ===================================================================================================== */

void TileMap::loadFromFile(const std::string file_path)
{
    std::ifstream in_file;

    // Try to open a file.
    in_file.open(file_path);

    // If couldn'd open file, runtime error.
    if (!in_file.is_open())
        ErrorHandler::throwErr("TILEMAP::LOADFROMFILE::ERR_COULD_NOT_LOAD_TILEMAP_FROM_FILE\n");

    // CONFIG DATA
    unsigned map_grid_width = 0;
    unsigned map_grid_height = 0;
    int grid_size = 0;

    unsigned layers = 0;

    std::string texture_file_path;

    // TILE DATA
    short type = TileType::DEFAULT;

    int grid_x = 0;
    int grid_y = 0;
    unsigned z = 0;
    unsigned k = 0;

    unsigned txtr_rect_top;
    unsigned txtr_rect_left;

    bool collision = false;

    float coll_box_width = 0.f;
    float coll_box_height = 0.f;
    float coll_box_offset_x = 0.f;
    float coll_box_offset_y = 0.f;

    // Load CONFIG
    in_file >> map_grid_width >> map_grid_height >> grid_size >> layers >> texture_file_path;

    this->gridSizeF = (float)grid_size;
    this->gridSizeI = grid_size;
    this->layers = layers;

    this->mapGridDimensions.x = map_grid_width;
    this->mapGridDimensions.y = map_grid_height;

    this->mapWorldDimensions.x = static_cast<float>(map_grid_width) * gridSizeF;
    this->mapWorldDimensions.y = static_cast<float>(map_grid_height) * gridSizeF;

    this->texture_file_path = texture_file_path;

    // If failed to load texture
    if (!this->tileTextureSheet.loadFromFile(texture_file_path))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

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
    while (in_file >> grid_x >> grid_y >> z >> k >> type)
    {
        // Spanwers
        if (static_cast<TileType>(type) == TileType::SPAWNER)
        {
            // SPAWNER SPECIFIC DATA
            int enemy_type = 0;
            int enemy_amount = 0;
            int enemy_time_to_spawn = 0;
            int enemy_max_distance = 0;

            in_file >> txtr_rect_top >> txtr_rect_left >> enemy_type >>
                enemy_amount >> enemy_time_to_spawn >> enemy_max_distance;

            this->map[grid_x][grid_y][z].insert(
                this->map[grid_x][grid_y][z].begin() + k,
                new EnemySpawnerTile(
                    grid_x, grid_y, this->gridSizeF, this->tileTextureSheet,
                    sf::IntRect(txtr_rect_top, txtr_rect_left, this->gridSizeI, this->gridSizeI),
                    enemy_type, enemy_amount, enemy_time_to_spawn, enemy_max_distance));
        }
        // Common tiles
        else
        {
            in_file >> txtr_rect_top >> txtr_rect_left >> collision >>
                coll_box_width >> coll_box_height >> coll_box_offset_x >> coll_box_offset_y;

            this->map[grid_x][grid_y][z].insert(
                this->map[grid_x][grid_y][z].begin() + k,
                new RegularTile(
                    static_cast<TileType>(type),
                    grid_x, grid_y, this->gridSizeF, this->tileTextureSheet,
                    sf::IntRect(txtr_rect_top, txtr_rect_left, this->gridSizeI, this->gridSizeI),
                    collision,
                    coll_box_width, coll_box_height,
                    coll_box_offset_x, coll_box_offset_y));
        }
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

    // CONFIG data
    out_file << this->mapGridDimensions.x << " " << this->mapGridDimensions.y << "\n"
             << this->gridSizeI << "\n"
             << this->layers << "\n"
             << this->texture_file_path << "\n";

    // Write all tiles information
    for (size_t x = 0; x < this->mapGridDimensions.x; x++)
    {
        for (size_t y = 0; y < this->mapGridDimensions.y; y++)
        {
            for (size_t z = 0; z < this->layers; z++)
            {
                if (!this->map[x][y][z].empty())
                {
                    for (size_t k = 0; k < this->map[x][y][z].size(); k++)
                    {
                        out_file << x << " " << y << " " << z << " " << k << " "
                                 << this->map[x][y][z][k]->getPropertiesAsString()
                                 << "\n";
                    }
                }
            }
        }
    }

    out_file.close();
}

void TileMap::addTile(
    const unsigned x, const unsigned y, const unsigned z,
    const sf::IntRect &texture_rect,
    const bool &collision,
    const float coll_box_width, const float coll_box_height,
    const float coll_box_offset_x, const float coll_box_offset_y,
    const TileType &type)
{
    // If position is in the map bounds
    if (x < this->mapGridDimensions.x && y < this->mapGridDimensions.y && z < this->layers)
    {
        if (!this->map[x][y][z].empty())
        {
            // If the texture of the tile to be placed is not equal to
            // the texture of the tile already on the vector
            if (this->map[x][y][z].back()->getTextureRect() != texture_rect)
            {
                this->map[x][y][z].push_back(new RegularTile(type,
                                                             x, y, this->gridSizeF, this->tileTextureSheet,
                                                             texture_rect, collision,
                                                             coll_box_width, coll_box_height,
                                                             coll_box_offset_x, coll_box_offset_y));
            }
        }
        else
        {
            this->map[x][y][z].push_back(new RegularTile(type,
                                                         x, y, this->gridSizeF, this->tileTextureSheet,
                                                         texture_rect, collision,
                                                         coll_box_width, coll_box_height,
                                                         coll_box_offset_x, coll_box_offset_y));
        }
    }
}

void TileMap::addSpawner(
    const unsigned x, const unsigned y, const unsigned z,
    const sf::IntRect &texture_rect,
    const int enemy_type, const int enemy_amount,
    const int enemy_time_to_spawn, const int enemy_max_distance)
{
    // If position is in the map bounds
    if (x < this->mapGridDimensions.x && y < this->mapGridDimensions.y && z < this->layers)
    {
        if (!this->map[x][y][z].empty())
        {
            // If the texture of the spawner to be placed is not equal to
            // the texture of the tile already on the vector
            if (this->map[x][y][z].back()->getTextureRect() != texture_rect)
            {
                this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileTextureSheet,
                                                                  texture_rect,
                                                                  enemy_type, enemy_amount,
                                                                  enemy_time_to_spawn, enemy_max_distance));
            }
        }
        else
        {
            this->map[x][y][z].push_back(new EnemySpawnerTile(x, y, this->gridSizeF, this->tileTextureSheet,
                                                              texture_rect,
                                                              enemy_type, enemy_amount,
                                                              enemy_time_to_spawn, enemy_max_distance));
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned layer)
{
    // If position is in the map bounds
    if (x < this->mapGridDimensions.x && y < this->mapGridDimensions.y && layer < this->layers)
    {
        // If the place to remove is not empty
        if (!this->map[x][y][layer].empty())
        {
            delete this->map[x][y][layer].back();
            this->map[x][y][layer].pop_back();
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
    else if (entity->getPosition().x + entity->getSize().x > this->mapWorldDimensions.x)
    {
        entity->stopVelocityX();
        entity->setPosition(
            sf::Vector2f(this->mapWorldDimensions.x - entity->getSize().x, entity->getPosition().y));
    }

    // Y axis
    if (entity->getPosition().y < 0.f)
    {
        entity->stopVelocityY();
        entity->setPosition(sf::Vector2f(entity->getPosition().x, 0.f));
    }
    else if (entity->getPosition().y + entity->getSize().y > this->mapWorldDimensions.y)
    {
        entity->stopVelocityY();
        entity->setPosition(
            sf::Vector2f(entity->getPosition().x, this->mapWorldDimensions.y - entity->getSize().y));
    }

    /* TILES */

    this->updateMapActiveArea(entity, 5, 5);

    for (size_t x = this->startX; x < this->endX; x++)
    {
        for (size_t y = this->startY; y < this->endY; y++)
        {
            for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
            {
                this->map[x][y][this->layer][k]->update();

                if (this->map[x][y][this->layer][k]->isCollideable())
                {
                    sf::FloatRect entity_bounds = entity->getGlobalBounds();
                    sf::FloatRect wall_bounds = this->map[x][y][this->layer][k]->getGlobalBounds();
                    sf::FloatRect next_position_bounds = entity->getNextPositionBounds(dt);

                    if (next_position_bounds.intersects(wall_bounds))
                    {
                        if (entity->getDirection() == "UP")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + dt * (entity->getMaxVelocity() / 4.f)));
                        }
                        if (entity->getDirection() == "DOWN")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - dt * (entity->getMaxVelocity() / 4.f)));
                        }
                        if (entity->getDirection() == "LEFT")
                        {
                            entity->stopVelocityX();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x + dt * (entity->getMaxVelocity() / 4.f), entity->getPosition().y));
                        }
                        if (entity->getDirection() == "RIGHT")
                        {
                            entity->stopVelocityX();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x - dt * (entity->getMaxVelocity() / 4.f), entity->getPosition().y));
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
    const sf::Vector2f light_pos)
{
    int active_area_width = static_cast<int>(std::ceil(static_cast<float>(vm.width) / this->gridSizeF)) + 2;
    int active_area_height = static_cast<int>(std::ceil(static_cast<float>(vm.height) / this->gridSizeF) + 2);

    this->updateMapActiveArea(grid_position, active_area_width, active_area_height);

    for (size_t x = this->startX; x < this->endX; x++)
    {
        for (size_t y = this->startY; y < this->endY; y++)
        {
            for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
            {
                if (this->map[x][y][this->layer][k]->getType() == TileType::DOODAD && use_deferred_render)
                {
                    this->deferredTileRendering.push(this->map[x][y][this->layer][k]);
                }
                else
                {
                    if (this->map[x][y][this->layer][k]->getType() != TileType::SPAWNER)
                    {
                        if (shader)
                            this->map[x][y][this->layer][k]->render(target, shader, light_pos);
                        else
                            this->map[x][y][this->layer][k]->render(target);
                    }
                }

                if (show_collision_box)
                {
                    if (this->map[x][y][this->layer][k]->isCollideable())
                    {
                        target.draw(this->map[x][y][this->layer][k]->getCollisionBox());
                    }
                    if (this->map[x][y][this->layer][k]->getType() == TileType::SPAWNER)
                    {
                        this->map[x][y][this->layer][k]->render(target);
                    }
                }
            }
        }
    }
}

void TileMap::deferredRender(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
{
    while (!this->deferredTileRendering.empty())
    {
        if (shader)
            this->deferredTileRendering.top()->render(target, shader, light_pos);
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
    else if (this->startX >= this->mapGridDimensions.x)
        this->startX = this->mapGridDimensions.x;

    this->endX = entity->getGridPosition(this->gridSizeI).x + (width / 2) + 1;
    if (this->endX < 0)
        this->endX = 0;
    else if (this->endX >= this->mapGridDimensions.x)
        this->endX = this->mapGridDimensions.x;

    this->startY = entity->getGridPosition(this->gridSizeI).y - height / 2;
    if (this->startY < 0)
        this->startY = 0;
    else if (this->startY >= this->mapGridDimensions.x)
        this->startY = this->mapGridDimensions.y;

    this->endY = entity->getGridPosition(this->gridSizeI).y + (height / 2) + 1;
    if (this->endY < 0)
        this->endY = 0;
    else if (this->endY >= this->mapGridDimensions.y)
        this->endY = this->mapGridDimensions.y;
}

void TileMap::updateMapActiveArea(const sf::Vector2i grid_position, const int width, const int height)
{
    this->layer = 0;

    this->startX = grid_position.x - width / 2;
    if (this->startX < 0)
        this->startX = 0;
    else if (this->startX >= this->mapGridDimensions.x)
        this->startX = this->mapGridDimensions.x;

    this->endX = grid_position.x + width / 2 + 1;
    if (this->endX < 0)
        this->endX = 0;
    else if (this->endX >= this->mapGridDimensions.x)
        this->endX = this->mapGridDimensions.x;

    this->startY = grid_position.y - height / 2;
    if (this->startY < 0)
        this->startY = 0;
    else if (this->startY >= this->mapGridDimensions.x)
        this->startY = this->mapGridDimensions.y;

    this->endY = grid_position.y + height / 2 + 1;
    if (this->endY < 0)
        this->endY = 0;
    else if (this->endY >= this->mapGridDimensions.y)
        this->endY = this->mapGridDimensions.y;
}

/* ACCESSORS =================================================================================================== */

const bool TileMap::compareType(const int x, const int y, const unsigned layer, const TileType &type) const
{
    if (!this->isTileEmpty(x, y, layer))
        return this->map[x][y][layer].back()->getType() == type;

    return false;
}

const sf::Vector2f &TileMap::getSize() const
{
    return this->mapWorldDimensions;
}

const sf::Texture *TileMap::getTileTextureSheet() const
{
    return &this->tileTextureSheet;
}

const int TileMap::getAmountOfStackedTiles(const int x, const int y, const unsigned layer) const
{
    if (x >= 0 && x < this->mapGridDimensions.x &&
        y >= 0 && y < this->mapGridDimensions.y &&
        layer >= 0 && layer < this->layers)
        return static_cast<int>(this->map[x][y][layer].size());

    return -1;
}

const bool TileMap::isTileEmpty(const int x, const int y, const unsigned layer) const
{
    if (x >= 0 && x < this->mapGridDimensions.x &&
        y >= 0 && y < this->mapGridDimensions.y &&
        layer >= 0 && layer < this->layers)
    {
        if (!this->map[x][y][layer].empty())
            return false;
    }

    return true;
}
