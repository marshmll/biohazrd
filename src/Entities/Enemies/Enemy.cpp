#include "stdafx.h"
#include "Enemy.h"

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Enemy::Enemy(const short unsigned exp_drop)
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

const short unsigned Enemy::getExpDrop() const
{
    return expDrop;
}

/* FUNCTIONS ==================================================================================================== */

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
