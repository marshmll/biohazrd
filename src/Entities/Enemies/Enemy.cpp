#include "stdafx.h"
#include "Enemy.h"

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Enemy::Enemy(const std::string name, EnemySpawnerTile &enemy_spawner_tile, const short unsigned exp_drop)
    : Entity(name), enemySpawnerTile(enemy_spawner_tile)
{
    expDrop = exp_drop;
}

Enemy::~Enemy()
{
}

/* FUNCTIONS ==================================================================================================== */

void Enemy::earnHp(const short unsigned hp_amount)
{
    if (attributeComponent)
        attributeComponent->earnHp(hp_amount);
    else
        ErrorHandler::printErr("ENEMY::EARNHP::WARNING_NULLPTR_ATTRIBUTECOMPONENT");
}

void Enemy::loseHp(const short unsigned hp_amount)
{
    if (attributeComponent)
        attributeComponent->loseHp(hp_amount);
    else
        ErrorHandler::printErr("ENEMY::LOSEHP::WARNING_NULLPTR_ATTRIBUTECOMPONENT");
}

/* ACCESSORS ==================================================================================================== */

EnemySpawnerTile &Enemy::getEnemySpawnerTile()
{
    return enemySpawnerTile;
}

const short unsigned Enemy::getExpDrop() const
{
    return expDrop;
}

const AttributeComponent *Enemy::getAttributeComponent() const
{
    if (attributeComponent)
    {
        return attributeComponent;
    }
    else
    {
        ErrorHandler::printErr("ENEMY::GETATTRIBUTECOMPONENT::WARNING_RETURNING_NULLPTR_ATTRIBUTECOMPONENT");

        return nullptr;
    }
}
