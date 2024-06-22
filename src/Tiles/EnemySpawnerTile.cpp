#include "stdafx.h"
#include "EnemySpawnerTile.h"

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

EnemySpawnerTile::EnemySpawnerTile(
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const sf::Texture &texture, const sf::IntRect texture_rect,
    const int enemy_type, const int enemy_amount,
    const int enemy_time_to_spawn, const int enemy_max_distance)

    : Tile(TileType::SPAWNER, grid_x, grid_y, grid_size_f, texture, texture_rect,
           NOT_COLLIDEABLE, grid_size_f, grid_size_f, 0.f, 0.f)
{
    enemyType = enemy_type;
    enemyAmount = enemy_amount;
    enemyTimeToSpawn = enemy_time_to_spawn;
    enemyMaxDistance = enemy_max_distance;

    spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

/* FUNCTIONS ================================================================================================== */

void EnemySpawnerTile::update()
{
}

void EnemySpawnerTile::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);

        target.draw(tile, shader);
    }
    else
    {
        target.draw(tile);
    }
}

const bool &EnemySpawnerTile::hasSpawned() const
{
    return spawned;
}

/* ACCESSORS ================================================================================================== */

const std::string EnemySpawnerTile::getPropertiesAsString() const
{
    std::stringstream properties;

    properties << type << " "
               << tile.getTextureRect().left << " " << tile.getTextureRect().top << " "
               << enemyType << " " << enemyAmount << " "
               << enemyTimeToSpawn << " " << enemyMaxDistance;

    return properties.str();
}

/* MODIFIERS ==================================================================================================== */

void EnemySpawnerTile::setSpawned(const bool spawned)
{
    this->spawned = spawned;
}
