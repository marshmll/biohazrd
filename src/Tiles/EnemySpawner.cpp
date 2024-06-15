#include "stdafx.h"
#include "EnemySpawner.h"

/* CONSTRUCTOR AND DESTRUCTOR */

EnemySpawner::EnemySpawner(
    const int enemy_type, const int enemy_amount, const int enemy_time_to_spawn, const int enemy_max_distance,
    const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
    const sf::Texture &texture, const sf::IntRect texture_rect)
    : Tile(grid_x, grid_y, grid_size_f, texture, texture_rect, false, TileTypes::SPAWNER)
{
    this->enemyType = enemy_type;
    this->enemyAmount = enemy_amount;
    this->enemyTimeToSpawn = enemy_time_to_spawn;
    this->enemyMaxDistance = enemy_max_distance;
}

EnemySpawner::~EnemySpawner()
{
}

/* FUNCTIONS */

void EnemySpawner::update()
{
}

void EnemySpawner::render(sf::RenderTarget &target, sf::Shader *shader, const sf::Vector2f light_pos)
{
    if (shader)
    {
        shader->setUniform("hasTexture", true);
        shader->setUniform("lightPos", light_pos);

        target.draw(this->tile, shader);
    }
    else
    {
        target.draw(this->tile);
    }
}
