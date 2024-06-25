#include "stdafx.h"
#include "EnemySystem.h"

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

EnemySystem::EnemySystem(std::vector<Enemy *> &active_enemies, std::map<std::string, sf::Texture> &textures)
    : activeEnemies(active_enemies), textures(textures)
{
}

EnemySystem::~EnemySystem()
{
}

/* FUNCTIONS ===================================================================================================== */

void EnemySystem::update(const float &dt)
{
}

void EnemySystem::render(sf::RenderTarget &target)
{
}

void EnemySystem::createEnemy(const EnemyType type, const float x, const float y)
{
    switch (type)
    {
    case EnemyType::GREEN_SLIME:
        activeEnemies.push_back(new GreenSlime(x, y, textures["SLIME_SPRITESHEET"]));
        break;

    default:
        ErrorHandler::throwErr("ENEMYSYSTEM::CREATEENEMY::ERR_INVALID_ENEMY_TYPE\n");
    }
}

void EnemySystem::createEnemy(const EnemyType type, const sf::Vector2f position)
{
    switch (type)
    {
    case EnemyType::GREEN_SLIME:
        activeEnemies.push_back(new GreenSlime(position.x, position.y, textures["SLIME_SPRITESHEET"]));
        break;

    default:
        ErrorHandler::throwErr("ENEMYSYSTEM::CREATEENEMY::ERR_INVALID_ENEMY_TYPE\n");
    }
}

void EnemySystem::deleteEnemy(const size_t index)
{
    if (index >= activeEnemies.size())
        ErrorHandler::throwErr("ENEMYSSYTEM::DELETEENEMY::ERR_OUT_OF_BOUNDS_INDEX: " + index);

    delete activeEnemies[index];
    activeEnemies.erase(activeEnemies.begin() + index);
}

void EnemySystem::deleteEnemy(Enemy *enemy)
{
    auto enemy_it = std::find(activeEnemies.begin(), activeEnemies.end(), enemy);

    if (enemy_it == activeEnemies.end())
        ErrorHandler::throwErr("ENEMYSSYTEM::DELETEENEMY::ENEMY_POINTER_NOT_IN_VECTOR");

    delete enemy;
    activeEnemies.erase(enemy_it);
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */