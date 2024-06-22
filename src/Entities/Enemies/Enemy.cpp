#include "stdafx.h"
#include "Enemy.h"

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

/* FUNCTIONS ==================================================================================================== */

void Enemy::earnHp(const short unsigned hp_amount)
{
    if (attributeComponent)
        attributeComponent->earnHp(hp_amount);
}

void Enemy::loseHp(const short unsigned hp_amount)
{
    if (attributeComponent)
        attributeComponent->loseHp(hp_amount);
}

/* FUNCTIONS ==================================================================================================== */

AttributeComponent *Enemy::getAttributeComponent()
{
    return attributeComponent;
}
