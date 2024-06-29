#include "stdafx.h"
#include "EnemySpawnerTile.h"

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

EnemySpawnerTile::EnemySpawnerTile(
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const Texture &texture, const IntRect texture_rect,
    const short enemy_type, const short enemy_amount,
    const short enemy_time_to_spawn, const short enemy_max_distance,
    const short enemy_spawn_area_size)

    : Tile(SPAWNER, grid_x, grid_y, grid_size_f,
           texture, texture_rect,
           NOT_COLLIDEABLE, grid_size_f, grid_size_f, 0.f, 0.f)
{
    spawnTimer.restart();

    enemyType = enemy_type;
    enemyAmount = enemy_amount;
    enemyCounter = 0;
    enemyTimeToSpawn = enemy_time_to_spawn;
    enemyMaxDistance = enemy_max_distance;
    enemySpawnAreaSize = enemy_spawn_area_size;

    spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

/* FUNCTIONS ================================================================================================== */

void EnemySpawnerTile::update()
{
}

void EnemySpawnerTile::render(RenderTarget &target, Shader *shader, const Vector2f light_pos)
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

const bool EnemySpawnerTile::canSpawn(const Vector2f &player_pos)
{
    if (hasElapsedSpawnTime() && !hasSpawnedAllEnemies())
        return isPlayerInsideSpawnArea(player_pos);

    return false;
}

const bool EnemySpawnerTile::hasElapsedSpawnTime()
{
    if (static_cast<short>(spawnTimer.getElapsedTime().asSeconds()) >= enemyTimeToSpawn)
    {
        spawnTimer.restart();
        return true;
    }

    return false;
}

const bool EnemySpawnerTile::isPlayerInsideSpawnArea(const Vector2f &player_pos)
{
    Vector2f center = getCenteredPosition();

    short distance = static_cast<short>(sqrt(pow(player_pos.x - center.x, 2) + pow(player_pos.y - center.y, 2)));

    return distance <= enemySpawnAreaSize * gridSizeF;
}

const bool EnemySpawnerTile::hasSpawnedAllEnemies() const
{
    return enemyCounter >= enemyAmount;
}

void EnemySpawnerTile::increaseEnemyCounter()
{
    if (enemyCounter < enemyAmount)
        ++enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
    if (enemyCounter > 0)
        --enemyCounter;
}

/* ACCESSORS ================================================================================================== */

const short &EnemySpawnerTile::getEnemyCounter() const
{
    return enemyCounter;
}

const string EnemySpawnerTile::getPropertiesAsString() const
{
    stringstream properties;

    properties << type << " "
               << tile.getTextureRect().left << " " << tile.getTextureRect().top << " "
               << enemyType << " " << enemyAmount << " "
               << enemyTimeToSpawn << " " << enemyMaxDistance << " "
               << enemySpawnAreaSize;

    return properties.str();
}

/* MODIFIERS ==================================================================================================== */
