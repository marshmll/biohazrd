#include "stdafx.h"
#include "EnemySpawner.h"

/* CONSTRUCTOR AND DESTRUCTOR */

EnemySpawner::EnemySpawner(const sf::Vector2i grid_position, const float grid_size, const int type,
                           const int amount, const int spawn_timer, const int max_distance)
{
    this->shape.setSize(sf::Vector2f(grid_size, grid_size));
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setPosition(static_cast<float>(grid_position.x), static_cast<float>(grid_position.y));

    this->gridPosition = grid_position;
    this->gridSize = grid_size;
    this->type = type;
    this->amount = amount;
    this->spawnTimer = spawn_timer;
    this->maxDistance = max_distance;
}

EnemySpawner::~EnemySpawner()
{
}

/* FUNCTIONS */

void EnemySpawner::update(const float &dt)
{
}

void EnemySpawner::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
}
