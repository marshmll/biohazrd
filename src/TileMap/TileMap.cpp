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
    for (auto &x : map)
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

    map.clear();
}

void TileMap::resize(const int size_x, const int size_y, const int layers)
{
    map.resize(size_x, std::vector<std::vector<std::vector<Tile *>>>());

    for (size_t x = 0; x < map.size(); x++)
    {
        map[x].resize(size_y, std::vector<std::vector<Tile *>>());

        for (size_t y = 0; y < map[x].size(); y++)
        {
            map[x][y].resize(layers, std::vector<Tile *>());
        }
    }
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

TileMap::TileMap(const float grid_size, const unsigned map_grid_width, const unsigned map_grid_height,
                 const std::string texture_file_path)
{
    gridSizeF = grid_size;
    gridSizeI = (int)gridSizeF;
    layers = 1;

    mapGridDimensions.x = map_grid_width;
    mapGridDimensions.y = map_grid_height;

    mapWorldDimensions.x = map_grid_width * grid_size;
    mapWorldDimensions.y = map_grid_height * grid_size;

    resize(map_grid_width, map_grid_height, layers);

    textureFilePath = texture_file_path;

    if (!tileTextureSheet.loadFromFile(textureFilePath))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

    startX = 0;
    endX = 0;
    startY = 0;
    endY = 0;
    layer = 0;
}

TileMap::TileMap(const std::string map_file_path)
{
    loadFromFile(map_file_path);
}

TileMap::~TileMap()
{
    clear();
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

    // METADATA
    std::string title;
    std::string description;
    std::time_t creation_time;

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

    // Load METADATA
    std::getline(in_file, title);
    std::getline(in_file, description);
    in_file >> creation_time;

    this->title = title;
    this->description = description;
    this->creation_time = creation_time;

    // Load CONFIG DATA
    in_file >> map_grid_width >> map_grid_height >> grid_size >> layers >> texture_file_path;

    gridSizeF = (float)grid_size;
    gridSizeI = grid_size;
    layers = layers;

    mapGridDimensions.x = map_grid_width;
    mapGridDimensions.y = map_grid_height;

    mapWorldDimensions.x = static_cast<float>(map_grid_width) * gridSizeF;
    mapWorldDimensions.y = static_cast<float>(map_grid_height) * gridSizeF;

    texture_file_path = texture_file_path;

    // If failed to load texture
    if (!tileTextureSheet.loadFromFile(texture_file_path))
        ErrorHandler::throwErr("TILEMAP::TILEMAP::ERROR_COULD_NOT_LOAD_TILE_TEXTURES_FILE\n");

    startX = 0;
    endX = 0;
    startY = 0;
    endY = 0;
    layer = 0;

    // Clear the map
    clear();

    // Resize the map
    resize(map_grid_width, map_grid_height, layers);

    // While not in the end of file
    while (in_file >> grid_x >> grid_y >> z >> k >> type)
    {
        // Spanwers
        if (static_cast<TileType>(type) == TileType::SPAWNER)
        {
            // SPAWNER SPECIFIC DATA
            short enemy_type = 0;
            short enemy_amount = 0;
            short enemy_time_to_spawn = 0;
            short enemy_max_distance = 0;
            short enemy_spawn_area_size = 0;

            in_file >> txtr_rect_top >> txtr_rect_left >> enemy_type >>
                enemy_amount >> enemy_time_to_spawn >> enemy_max_distance >>
                enemy_spawn_area_size;

            map[grid_x][grid_y][z].insert(
                map[grid_x][grid_y][z].begin() + k,
                new EnemySpawnerTile(
                    grid_x, grid_y, gridSizeF, tileTextureSheet,
                    sf::IntRect(txtr_rect_top, txtr_rect_left, gridSizeI, gridSizeI),
                    enemy_type, enemy_amount, enemy_time_to_spawn,
                    enemy_max_distance, enemy_spawn_area_size));
        }
        // Common tiles
        else
        {
            in_file >> txtr_rect_top >> txtr_rect_left >> collision >>
                coll_box_width >> coll_box_height >> coll_box_offset_x >> coll_box_offset_y;

            map[grid_x][grid_y][z].insert(
                map[grid_x][grid_y][z].begin() + k,
                new RegularTile(
                    static_cast<TileType>(type),
                    grid_x, grid_y, gridSizeF, tileTextureSheet,
                    sf::IntRect(txtr_rect_top, txtr_rect_left, gridSizeI, gridSizeI),
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
    out_file << mapGridDimensions.x << " " << mapGridDimensions.y << "\n"
             << gridSizeI << "\n"
             << layers << "\n"
             << textureFilePath << "\n";

    // Write all tiles information
    for (size_t x = 0; x < mapGridDimensions.x; x++)
    {
        for (size_t y = 0; y < mapGridDimensions.y; y++)
        {
            for (size_t z = 0; z < layers; z++)
            {
                if (!map[x][y][z].empty())
                {
                    for (size_t k = 0; k < map[x][y][z].size(); k++)
                    {
                        out_file << x << " " << y << " " << z << " " << k << " "
                                 << map[x][y][z][k]->getPropertiesAsString()
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
    if (x < mapGridDimensions.x && y < mapGridDimensions.y && z < layers)
    {
        if (!map[x][y][z].empty())
        {
            // If the texture of the tile to be placed is not equal to
            // the texture of the tile already on the vector
            if (map[x][y][z].back()->getTextureRect() != texture_rect)
            {
                map[x][y][z].push_back(new RegularTile(type,
                                                       x, y, gridSizeF, tileTextureSheet,
                                                       texture_rect, collision,
                                                       coll_box_width, coll_box_height,
                                                       coll_box_offset_x, coll_box_offset_y));
            }
        }
        else
        {
            map[x][y][z].push_back(new RegularTile(type,
                                                   x, y, gridSizeF, tileTextureSheet,
                                                   texture_rect, collision,
                                                   coll_box_width, coll_box_height,
                                                   coll_box_offset_x, coll_box_offset_y));
        }
    }
}

void TileMap::addSpawner(
    const unsigned x, const unsigned y, const unsigned z,
    const sf::IntRect &texture_rect,
    const short enemy_type, const short enemy_amount,
    const short enemy_time_to_spawn, const short enemy_max_distance,
    const short enemy_spawn_area_size)
{
    // If position is in the map bounds
    if (x < mapGridDimensions.x && y < mapGridDimensions.y && z < layers)
    {
        if (!map[x][y][z].empty())
        {
            // If the texture of the spawner to be placed is not equal to
            // the texture of the tile already on the vector
            if (map[x][y][z].back()->getTextureRect() != texture_rect)
            {
                map[x][y][z].push_back(new EnemySpawnerTile(x, y, gridSizeF, tileTextureSheet,
                                                            texture_rect,
                                                            enemy_type, enemy_amount,
                                                            enemy_time_to_spawn, enemy_max_distance,
                                                            enemy_spawn_area_size));
            }
        }
        else
        {
            map[x][y][z].push_back(new EnemySpawnerTile(x, y, gridSizeF, tileTextureSheet,
                                                        texture_rect,
                                                        enemy_type, enemy_amount,
                                                        enemy_time_to_spawn, enemy_max_distance,
                                                        enemy_spawn_area_size));
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned layer)
{
    // If position is in the map bounds
    if (x < mapGridDimensions.x && y < mapGridDimensions.y && layer < layers)
    {
        // If the place to remove is not empty
        if (!map[x][y][layer].empty())
        {
            delete map[x][y][layer].back();
            map[x][y][layer].pop_back();
        }
    }
}

void TileMap::update(const float &dt, Entity *entity)
{
    updateMapActiveArea(entity, 5, 5);
}

void TileMap::render(
    sf::RenderTarget &target, const sf::Vector2i &grid_position, sf::VideoMode &vm,
    const bool show_collision_box, const bool use_deferred_render, sf::Shader *shader,
    const sf::Vector2f light_pos)
{
    int active_area_width = static_cast<int>(std::ceil(static_cast<float>(vm.width) / gridSizeF)) + 2;
    int active_area_height = static_cast<int>(std::ceil(static_cast<float>(vm.height) / gridSizeF) + 2);

    updateMapActiveArea(grid_position, active_area_width, active_area_height);

    for (size_t x = startX; x < endX; x++)
    {
        for (size_t y = startY; y < endY; y++)
        {
            for (size_t k = 0; k < map[x][y][layer].size(); k++)
            {
                if (map[x][y][layer][k]->getType() == TileType::DOODAD && use_deferred_render)
                {
                    deferredTileRendering.push(map[x][y][layer][k]);
                }
                else
                {
                    if (map[x][y][layer][k]->getType() != TileType::SPAWNER)
                    {
                        if (shader)
                            map[x][y][layer][k]->render(target, shader, light_pos);
                        else
                            map[x][y][layer][k]->render(target);
                    }
                }

                if (show_collision_box)
                {
                    if (map[x][y][layer][k]->isCollideable())
                    {
                        target.draw(map[x][y][layer][k]->getCollisionBox());
                    }
                    if (map[x][y][layer][k]->getType() == TileType::SPAWNER)
                    {
                        map[x][y][layer][k]->render(target);
                    }
                }
            }
        }
    }
}

void TileMap::deferredRender(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
{
    while (!deferredTileRendering.empty())
    {
        if (shader)
            deferredTileRendering.top()->render(target, shader, light_pos);
        else
            deferredTileRendering.top()->render(target);

        deferredTileRendering.pop();
    }
}

void TileMap::updateWorldBoundsCollision(const float &dt, Entity *entity)
{
    // X axis
    if (entity->getPosition().x < 0.f)
    {
        entity->setPosition(sf::Vector2f(0.f, entity->getPosition().y));
        entity->stopVelocityX();
    }
    else if (entity->getPosition().x + entity->getSize().x > mapWorldDimensions.x)
    {
        entity->stopVelocityX();
        entity->setPosition(
            sf::Vector2f(mapWorldDimensions.x - entity->getSize().x, entity->getPosition().y));
    }

    // Y axis
    if (entity->getPosition().y < 0.f)
    {
        entity->stopVelocityY();
        entity->setPosition(sf::Vector2f(entity->getPosition().x, 0.f));
    }
    else if (entity->getPosition().y + entity->getSize().y > mapWorldDimensions.y)
    {
        entity->stopVelocityY();
        entity->setPosition(
            sf::Vector2f(entity->getPosition().x, mapWorldDimensions.y - entity->getSize().y));
    }
}

void TileMap::updateTileCollision(const float &dt, Entity *entity)
{
    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            for (size_t k = 0; k < map[x][y][layer].size(); k++)
            {
                if (map[x][y][layer][k]->isCollideable())
                {
                    sf::FloatRect entity_bounds = entity->getGlobalBounds();
                    sf::FloatRect wall_bounds = map[x][y][layer][k]->getGlobalBounds();
                    sf::FloatRect next_position_bounds = entity->getNextPositionBounds(dt);

                    if (next_position_bounds.intersects(wall_bounds))
                    {
                        if (entity->getDirection() == "UP")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + dt * (entity->getMaxVelocity() / 4.f)));
                        }
                        else if (entity->getDirection() == "DOWN")
                        {
                            entity->stopVelocityY();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - dt * (entity->getMaxVelocity() / 4.f)));
                        }
                        else if (entity->getDirection() == "LEFT")
                        {
                            entity->stopVelocityX();
                            entity->setPosition(sf::Vector2f(entity->getPosition().x + dt * (entity->getMaxVelocity() / 4.f), entity->getPosition().y));
                        }
                        else if (entity->getDirection() == "RIGHT")
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

void TileMap::updateTiles(const float &dt, Entity *entity, EnemySystem *enemySystem)
{
    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            for (size_t k = 0; k < map[x][y][layer].size(); k++)
            {
                map[x][y][layer][k]->update();

                if (map[x][y][layer][k]->getType() == TileType::SPAWNER)
                {
                    EnemySpawnerTile *est = dynamic_cast<EnemySpawnerTile *>(map[x][y][layer][k]);

                    if (est->canSpawn(entity->getCenteredPosition()))
                    {
                        enemySystem->createEnemy(GREEN_SLIME,
                                                 est->getPosition().x + rand() % 50,
                                                 est->getPosition().y + rand() % 50,
                                                 *est);
                    }
                }
            }
        }
    }
}

void TileMap::updateMapActiveArea(Entity *entity, const int width, const int height)
{
    layer = 0;

    startX = entity->getGridPosition(gridSizeI).x - width / 2;
    if (startX < 0)
        startX = 0;
    else if (startX >= mapGridDimensions.x)
        startX = mapGridDimensions.x;

    endX = entity->getGridPosition(gridSizeI).x + (width / 2) + 1;
    if (endX < 0)
        endX = 0;
    else if (endX >= mapGridDimensions.x)
        endX = mapGridDimensions.x;

    startY = entity->getGridPosition(gridSizeI).y - height / 2;
    if (startY < 0)
        startY = 0;
    else if (startY >= mapGridDimensions.x)
        startY = mapGridDimensions.y;

    endY = entity->getGridPosition(gridSizeI).y + (height / 2) + 1;
    if (endY < 0)
        endY = 0;
    else if (endY >= mapGridDimensions.y)
        endY = mapGridDimensions.y;
}

void TileMap::updateMapActiveArea(const sf::Vector2i grid_position, const int width, const int height)
{
    layer = 0;

    startX = grid_position.x - width / 2;
    if (startX < 0)
        startX = 0;
    else if (startX >= mapGridDimensions.x)
        startX = mapGridDimensions.x;

    endX = grid_position.x + width / 2 + 1;
    if (endX < 0)
        endX = 0;
    else if (endX >= mapGridDimensions.x)
        endX = mapGridDimensions.x;

    startY = grid_position.y - height / 2;
    if (startY < 0)
        startY = 0;
    else if (startY >= mapGridDimensions.x)
        startY = mapGridDimensions.y;

    endY = grid_position.y + height / 2 + 1;
    if (endY < 0)
        endY = 0;
    else if (endY >= mapGridDimensions.y)
        endY = mapGridDimensions.y;
}

/* ACCESSORS =================================================================================================== */

const bool TileMap::compareType(const int x, const int y, const unsigned layer, const TileType &type) const
{
    if (!isTileEmpty(x, y, layer))
        return map[x][y][layer].back()->getType() == type;

    return false;
}

const sf::Vector2f &TileMap::getSize() const
{
    return mapWorldDimensions;
}

const sf::Texture *TileMap::getTileTextureSheet() const
{
    return &tileTextureSheet;
}

const int TileMap::getAmountOfStackedTiles(const int x, const int y, const unsigned layer) const
{
    if (x >= 0 && x < mapGridDimensions.x &&
        y >= 0 && y < mapGridDimensions.y &&
        layer >= 0 && layer < layers)
        return static_cast<int>(map[x][y][layer].size());

    return -1;
}

const bool TileMap::isTileEmpty(const int x, const int y, const unsigned layer) const
{
    if (x >= 0 && x < mapGridDimensions.x &&
        y >= 0 && y < mapGridDimensions.y &&
        layer >= 0 && layer < layers)
    {
        if (!map[x][y][layer].empty())
            return false;
    }

    return true;
}
