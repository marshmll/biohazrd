#include "stdafx.h"
#include "EnemySystem.h"

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

EnemySystem::EnemySystem(vector<Enemy *> &active_enemies, map<string, Texture> &textures,
                         Entity &player)

    : activeEnemies(active_enemies), textures(textures), player(player)
{
}

EnemySystem::~EnemySystem()
{
}

/* FUNCTIONS ===================================================================================================== */

void EnemySystem::update(const float &dt)
{
}

void EnemySystem::render(RenderTarget &target)
{
}

void EnemySystem::createEnemy(const EnemyType type, const float x, const float y, EnemySpawnerTile &enemy_spawner_tile)
{
    switch (type)
    {
    case EnemyType::GREEN_SLIME:
        activeEnemies.push_back(new GreenSlime(enemy_spawner_tile, player, x, y, textures["SLIME_SPRITESHEET"]));
        enemy_spawner_tile.increaseEnemyCounter();
        break;

    default:
        ErrorHandler::throwErr("ENEMYSYSTEM::CREATEENEMY::ERR_INVALID_ENEMY_TYPE\n");
    }
}

void EnemySystem::createEnemy(const EnemyType type, const Vector2f position, EnemySpawnerTile &enemy_spawner_tile)
{
    switch (type)
    {
    case EnemyType::GREEN_SLIME:
        activeEnemies.push_back(new GreenSlime(enemy_spawner_tile, player, position.x, position.y, textures["SLIME_SPRITESHEET"]));
        enemy_spawner_tile.increaseEnemyCounter();
        break;

    default:
        ErrorHandler::throwErr("ENEMYSYSTEM::CREATEENEMY::ERR_INVALID_ENEMY_TYPE\n");
    }
}

void EnemySystem::deleteEnemy(const size_t index)
{
    if (index >= activeEnemies.size())
        ErrorHandler::throwErr("ENEMYSSYTEM::DELETEENEMY::ERR_OUT_OF_BOUNDS_INDEX: " + index);

    activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();

    delete activeEnemies[index];
    activeEnemies.erase(activeEnemies.begin() + index);
}

void EnemySystem::deleteEnemy(Enemy *enemy)
{
    auto enemy_it = find(activeEnemies.begin(), activeEnemies.end(), enemy);

    if (enemy_it == activeEnemies.end())
        ErrorHandler::throwErr("ENEMYSSYTEM::DELETEENEMY::ENEMY_POINTER_NOT_IN_VECTOR");

    enemy->getEnemySpawnerTile().decreaseEnemyCounter();

    delete enemy;
    activeEnemies.erase(enemy_it);
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */