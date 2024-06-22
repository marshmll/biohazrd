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

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */